#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <SPIFFS.h>
#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/Blob.h>
#include <CoreUtil/ArrayUtil.h>
#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>
#include <SSD1351/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerGL/Patterns.h>
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
		const size_t totalHeight = 48;
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

		size_t patternBeginOffset[BadgerGL::MAX_BIT_GRADIENT + 1];

		for ( uint32_t pattern = 0; pattern <= BadgerGL::MAX_BIT_GRADIENT; ++pattern )
		{
			patternBeginOffset[pattern] = pattern * (totalColumns / (BadgerGL::MAX_BIT_GRADIENT + 1));
		}

		renderer.setPrimaryColour(0x0000);
		renderer.setSecondaryColour(0xFFFF);

		for ( uint32_t pattern = 0; pattern <= BadgerGL::MAX_BIT_GRADIENT; ++pattern )
		{
			// Offset by 8 for outer padding
			const size_t beginX = 8 + patternBeginOffset[pattern];
			const size_t endX = 8 + (pattern < BadgerGL::MAX_BIT_GRADIENT ? patternBeginOffset[pattern + 1] : totalColumns);

			const size_t beginY = 128 - 8 - 16; // Screen height - outer padding - height of row
			const size_t endY = beginY + 16;

			Rect16 rect(Point16(beginX, beginY), Point16(endX, endY));

			renderer.setBitGradientDirection(pattern % 2 ? PatternDirection::Vertical : PatternDirection::Horizontal);
			renderer.setBitGradientType(static_cast<uint8_t>(pattern));
			renderer.drawPatterned(rect);
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
		using namespace PlatformConfig;

		const PlatformConfigObject* configObject = PlatformConfig::globalConfig();

		configObject->initialiseSubsystem<SerialConfig>(&testDelegatedSerialInit);

		BGRS_ASSERT(configObject->args().display == PlatformConfig::DisplayType::SSD1351, "SSD1351 display must be used.");

		// These are all required:
		const PlatformConfigObject::SPIConfig* spiConfig = configObject->getElement<PlatformConfigObject::SPIConfig>();
		const PlatformConfigObject::SPIPinConfig* spiPinConfig = configObject->getElement<PlatformConfigObject::SPIPinConfig>();
		const PlatformConfigObject::SSD1351Config* ssd1351Config = configObject->getElement<PlatformConfigObject::SSD1351Config>();
		const PlatformConfigObject::SerialConfig* serialConfig = configObject->getElement<PlatformConfigObject::SerialConfig>();
		const PlatformConfigObject::ChipSelectConfig* chipSelectConfig = configObject->getElement<PlatformConfigObject::ChipSelectConfig>();

		Serial.printf("Sanity test initialising...\r\n");
		Serial.printf("Version %s\r\n", PlatformConfig::Versions::VERSION_STRING_FULL);
		Serial.printf("\r\n");

		Serial.printf("=== Chip select configuration ===\r\n");
		Serial.printf("           Display: %u\r\n", chipSelectConfig->displayCSPin);
		Serial.printf("\r\n");

		Serial.printf("=== Serial configuration ===\r\n");
		Serial.printf("         Baud rate: %u\r\n", serialConfig->baudRate);
		Serial.printf("\r\n");

		Serial.printf("=== SSD1351 configuration ===\r\n");
		Serial.printf("             Reset: %u\r\n", ssd1351Config->resetPin);
		Serial.printf("      Data/command: %u\r\n", ssd1351Config->dataCommandPin);
		Serial.printf("\r\n");

		Serial.printf("=== SPI configuration ===\r\n");
		Serial.printf("         Data mode: %u\r\n", spiConfig->dataMode);
		Serial.printf("         Bit order: %u\r\n", spiConfig->bitOrder);
		Serial.printf("        Clock mode: %s\r\n", spiConfig->clockMode == PlatformConfig::SPIConfig::ClockRateMode::Divider ? "divider" : "frequency");
		Serial.printf("       Clock value: %u\r\n", spiConfig->clockValue);
		Serial.printf("         Clock pin: %u\r\n", spiPinConfig->clockPin);
		Serial.printf("          MISO pin: %u\r\n", spiPinConfig->misoPin);
		Serial.printf("          MOSI pin: %u\r\n", spiPinConfig->mosiPin);
		Serial.printf(" Write protect pin: %u\r\n", spiPinConfig->writeProtectPin);
		Serial.printf("          Hold pin: %u\r\n", spiPinConfig->holdPin);
		Serial.printf("\r\n");

		Serial.printf("Screen buffer dimensions: %ux%u, bit depth %u.\r\n", ScreenBufferSurface.width(), ScreenBufferSurface.height(), ScreenBufferSurface.bitDepth());
		Serial.printf("Screen buffer size: %u bytes.\r\n", ScreenBufferSurface.pixelDataSize());

		PlatformConfig::chipSelectSetup(*chipSelectConfig);
		PlatformConfig::spiSetup(*spiConfig);

		SPI.begin(spiPinConfig->clockPin,
				  spiPinConfig->misoPin,
				  spiPinConfig->mosiPin,
				  chipSelectConfig->displayCSPin);

		SSD1351::Driver.initialise(*ssd1351Config);

		prepareTestImage();
		testFileSystem();

		Serial.print("Sanity test initialised.\r\n");

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
