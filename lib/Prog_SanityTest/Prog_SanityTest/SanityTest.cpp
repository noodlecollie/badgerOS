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

#include "SanityTest.h"
#include "TestCardLayout.h"

namespace SanityTest
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
			Serial.printf("/hello.txt does not exist.\n");
			return;
		}

		Serial.printf("/hello.txt exists.\n");
		File file = SPIFFS.open("/hello.txt", "r");

		if ( !file )
		{
			Serial.printf("/hello.txt failed to open.\n");
			return;
		}

		char data[32];
		file.readBytes(data, sizeof(data));

		Serial.printf("First 32 bytes of data: %s\n", data);
		file.close();
	}

	static void testDelegatedSerialInit(const PlatformConfig::SerialConfig& config)
	{
		Serial.begin(config.baudRate);
	}

	void setup()
	{
		const PlatformConfig::Config& config = PlatformConfig::globalConfig();

		BGRS_ASSERT(config.ssd1351Config, "SSD1351 config is required.");
		BGRS_ASSERT(config.serialConfig, "Serial config is required.");
		BGRS_ASSERT(config.spiConfig, "SPI config is required.");
		BGRS_ASSERT(config.spiPinConfig, "SPI pin config is required.");
		BGRS_ASSERT(config.chipSelectConfig, "Chip select config is required.");

		//Serial.begin(config.serialConfig->baudRate);
		PlatformConfig::initialiseSubsystem(&PlatformConfig::Config::serialConfig, &testDelegatedSerialInit);

		Serial.printf("Sanity test initialising...\n");
		Serial.printf("Version %s\n", PlatformConfig::Versions::VERSION_STRING_FULL);
		Serial.printf("\n");

		Serial.printf("=== Chip select configuration ===\n");
		Serial.printf("              OLED: %u\n", config.chipSelectConfig->oledScreenCSPin);
		Serial.printf("\n");

		Serial.printf("=== Serial configuration ===\n");
		Serial.printf("         Baud rate: %u\n", config.serialConfig->baudRate);
		Serial.printf("\n");

		Serial.printf("=== SSD1351 configuration ===\n");
		Serial.printf("             Reset: %u\n", config.ssd1351Config->resetPin);
		Serial.printf("      Data/command: %u\n", config.ssd1351Config->dataCommandPin);
		Serial.printf("\n");

		Serial.printf("=== SPI configuration ===\n");
		Serial.printf("         Data mode: %u\n", config.spiConfig->dataMode);
		Serial.printf("         Bit order: %u\n", config.spiConfig->bitOrder);
		Serial.printf("     Clock divider: %u\n", config.spiConfig->clockDivider);
		Serial.printf("         Clock pin: %u\n", config.spiPinConfig->clockPin);
		Serial.printf("          MISO pin: %u\n", config.spiPinConfig->misoPin);
		Serial.printf("          MOSI pin: %u\n", config.spiPinConfig->mosiPin);
		Serial.printf(" Write protect pin: %u\n", config.spiPinConfig->writeProtectPin);
		Serial.printf("          Hold pin: %u\n", config.spiPinConfig->holdPin);
		Serial.printf("\n");

		Serial.printf("Screen buffer dimensions: %ux%u, bit depth %u.\n", ScreenBufferSurface.width(), ScreenBufferSurface.height(), ScreenBufferSurface.bitDepth());
		Serial.printf("Screen buffer size: %u bytes.\n", ScreenBufferSurface.pixelDataSize());

		PlatformConfig::chipSelectSetup(*config.chipSelectConfig);
		PlatformConfig::spiSetup(*config.spiConfig);

		SPI.begin(config.spiPinConfig->clockPin, config.spiPinConfig->misoPin, config.spiPinConfig->mosiPin, config.chipSelectConfig->oledScreenCSPin);
		SSD1351::Driver.initialise(*config.ssd1351Config);

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
