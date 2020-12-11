#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <SPIFFS.h>
#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/Blob.h>
#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>
#include <SSD1351/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/ColourScheme.h>

#include "SSD1351SanityTest.h"
#include "TestCardLayout.h"

namespace SSD1351SanityTest
{
	static BadgerGL::Static65KBitmapSurface<SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT> ScreenBufferSurface;

	static void prepareTestImage()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		ColourScheme colourScheme;
		colourScheme.setColour(ColourScheme::Colour_Background, col24To16(0x404040));
		colourScheme.setColour(ColourScheme::Colour_Primary, col24To16(0xFFD800));
		colourScheme.setColour(ColourScheme::Colour_Secondary, col24To16(0x7AFFFF));

		ScreenBufferSurface.fill(colourScheme.colour(ColourScheme::Colour_Background));

		BitmapRenderer renderer(&ScreenBufferSurface);

		UIDrawContext drawContext;
		drawContext.screenBuffer = &ScreenBufferSurface;
		drawContext.renderer = &renderer;
		drawContext.colourScheme = &colourScheme;

		TestCardLayout layout;
		layout.drawDirtyItems(drawContext);

		renderer.setShapeDrawStyle(ShapeDrawStyle::Filled);
		const size_t totalColumns = 128 - 16;	// Width - outer padding
		const size_t totalHeight = 128 - 16 - 32 - 8;	// Height - outer padding - top shapes - spacing
		const Point16 topLeft(8, 8 + 32 + 8);
		const size_t rowHeight = totalHeight / 4;

		for ( uint32_t column = 0; column < totalColumns; ++column )
		{
			const uint8_t colour = static_cast<uint8_t>(static_cast<float>(column * 255) / static_cast<float>(totalColumns));
			Rect16 rect(topLeft + Point16(column, 0), 1, rowHeight);

			renderer.setPrimaryColour(col24To16(colour << 16));
			renderer.draw(rect);

			renderer.setPrimaryColour(col24To16(colour << 8));
			rect.translate(Point16(0, rowHeight));
			renderer.draw(rect);

			renderer.setPrimaryColour(col24To16(colour));
			rect.translate(Point16(0, rowHeight));
			renderer.draw(rect);

			renderer.setPrimaryColour(col24To16((colour << 16) | (colour << 8) | colour));
			rect.translate(Point16(0, rowHeight));
			renderer.draw(rect);
		}
	}

	static void testFileSystem()
	{
		SPIFFS.begin();

		if ( !SPIFFS.exists("/hello.txt") )
		{
			Serial.printf("/hello.txt does not exist.\r\n");
			return;
		}

		Serial.printf("/hello.txt exists.\r\n");
		File file = SPIFFS.open("/hello.txt", "r");

		if ( !file )
		{
			Serial.printf("/hello.txt failed to open.\r\n");
			return;
		}

		char data[32];
		file.readBytes(data, sizeof(data));

		Serial.printf("First 32 bytes of data: %s\r\n", data);
		file.close();
	}

	static void testDelegatedSerialInit(const PlatformConfig::SerialConfig& config)
	{
		Serial.begin(config.baudRate);
	}

	void getPlatformConfigArgs(PlatformConfig::ConfigArgs& args)
	{
		args.display = PlatformConfig::DisplayType::SSD1351;
	}

	void setup()
	{
		const PlatformConfig::ConfigInstance& configInstance = PlatformConfig::globalConfig();
		const PlatformConfig::ConfigArgs& configArgs = configInstance.args();
		const PlatformConfig::ConfigData& configData = configInstance.data();

		BGRS_ASSERT(configData.serialConfig, "Serial config is required.");
		PlatformConfig::initialiseSubsystem(&PlatformConfig::ConfigData::serialConfig, &testDelegatedSerialInit);

		BGRS_ASSERT(configArgs.display == PlatformConfig::DisplayType::SSD1351, "SSD1351 display must be used.");
		BGRS_ASSERT(configInstance.ssd1351Config(), "SSD1351 config is required.");
		BGRS_ASSERT(configData.spiConfig, "SPI config is required.");
		BGRS_ASSERT(configData.spiPinConfig, "SPI pin config is required.");
		BGRS_ASSERT(configData.chipSelectConfig, "Chip select config is required.");

		Serial.printf("Sanity test initialising...\r\n");
		Serial.printf("Version %s\r\n", PlatformConfig::Versions::VERSION_STRING_FULL);
		Serial.printf("\r\n");

		Serial.printf("=== Chip select configuration ===\r\n");
		Serial.printf("           Display: %u\r\n", configData.chipSelectConfig->displayCSPin);
		Serial.printf("\r\n");

		Serial.printf("=== Serial configuration ===\r\n");
		Serial.printf("         Baud rate: %u\r\n", configData.serialConfig->baudRate);
		Serial.printf("\r\n");

		Serial.printf("=== SSD1351 configuration ===\r\n");
		Serial.printf("             Reset: %u\r\n", configInstance.ssd1351Config()->resetPin);
		Serial.printf("      Data/command: %u\r\n", configInstance.ssd1351Config()->dataCommandPin);
		Serial.printf("\r\n");

		Serial.printf("=== SPI configuration ===\r\n");
		Serial.printf("         Data mode: %u\r\n", configData.spiConfig->dataMode);
		Serial.printf("         Bit order: %u\r\n", configData.spiConfig->bitOrder);
		Serial.printf("        Clock mode: %s\r\n", configData.spiConfig->clockMode == PlatformConfig::SPIConfig::ClockRateMode::Divider ? "divider" : "frequency");
		Serial.printf("       Clock value: %u\r\n", configData.spiConfig->clockValue);
		Serial.printf("         Clock pin: %u\r\n", configData.spiPinConfig->clockPin);
		Serial.printf("          MISO pin: %u\r\n", configData.spiPinConfig->misoPin);
		Serial.printf("          MOSI pin: %u\r\n", configData.spiPinConfig->mosiPin);
		Serial.printf(" Write protect pin: %u\r\n", configData.spiPinConfig->writeProtectPin);
		Serial.printf("          Hold pin: %u\r\n", configData.spiPinConfig->holdPin);
		Serial.printf("\r\n");

		Serial.printf("Screen buffer dimensions: %ux%u, bit depth %u.\r\n", ScreenBufferSurface.width(), ScreenBufferSurface.height(), ScreenBufferSurface.bitDepth());
		Serial.printf("Screen buffer size: %u bytes.\r\n", ScreenBufferSurface.pixelDataSize());

		PlatformConfig::chipSelectSetup(*configData.chipSelectConfig);
		PlatformConfig::spiSetup(*configData.spiConfig);

		SPI.begin(configData.spiPinConfig->clockPin,
				  configData.spiPinConfig->misoPin,
				  configData.spiPinConfig->mosiPin,
				  configData.chipSelectConfig->displayCSPin);

		SSD1351::Driver.initialise(*configInstance.ssd1351Config());

		prepareTestImage();
		testFileSystem();

		Serial.println("Sanity test initialised.");

		SSD1351::Driver.clearScreen(0x0000);
		delay(500);
		SSD1351::Driver.clearScreen(0xFF00);
		delay(500);
		SSD1351::Driver.clearScreen(0x00FF);
		delay(500);
		SSD1351::Driver.writeImage(CoreUtil::ConstBlob(ScreenBufferSurface.rawPixelData(), ScreenBufferSurface.pixelDataSize()));
	}

	void loop()
	{
	}
}
