#include <CoreUtil/BgrsAssert.h>
#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <SSD1351/CustomDriver/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>

#include "SanityTest.h"

namespace SanityTest
{
	static BadgerGL::StaticBitmapSurface16<SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT> ScreenBufferSurface;

	void setup(PlatformConfig::ConfigFactoryFunc configFunc)
	{
		BGRS_ASSERT(configFunc, "Config factory function is required.");

		PlatformConfig::Config config;
		configFunc(config);

		BGRS_ASSERT(config.ssd1351Config, "SSD1351 config is required.");
		BGRS_ASSERT(config.serialConfig, "Serial config is required.");
		BGRS_ASSERT(config.spiConfig, "SPI config is required.");
		BGRS_ASSERT(config.spiPinConfig, "SPI pin config is required.");
		BGRS_ASSERT(config.chipSelectConfig, "Chip select config is required.");

		Serial.begin(config.serialConfig->baudRate);

		Serial.printf("Sanity test initialising...\n");
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
		Serial.printf("Screen buffer size: %u bytes.\n", ScreenBufferSurface.dataSize());

		PlatformConfig::chipSelectSetup(*config.chipSelectConfig);
		PlatformConfig::spiSetup(*config.spiConfig);

		SPI.begin(config.spiPinConfig->clockPin, config.spiPinConfig->misoPin, config.spiPinConfig->mosiPin, config.chipSelectConfig->oledScreenCSPin);
		SSD1351::Driver.initialise(*config.ssd1351Config);

		ScreenBufferSurface.fill(0xF0F0);
		ScreenBufferSurface.fillRect(BadgerGL::BitmapSurface::SurfaceRect(8, 64, 120, 120), 0xFF00);

		BadgerGL::BitmapRenderer renderer(ScreenBufferSurface);
		renderer.setPrimaryColour(0xFF00);
		renderer.setSecondaryColour(0x00FF);

		renderer.setShapeDrawStyle(BadgerGL::ShapeDrawStyle::Filled);
		renderer.draw(BadgerGL::Rect16(BadgerGL::Point16(8, 8), 32, 32));

		renderer.setLineWidth(4);
		renderer.setShapeDrawStyle(BadgerGL::ShapeDrawStyle::Outline);
		renderer.draw(BadgerGL::Rect16(BadgerGL::Point16(48, 8), 32, 32));

		renderer.setLineWidth(1);
		renderer.setShapeDrawStyle(BadgerGL::ShapeDrawStyle::FilledOutline);
		renderer.draw(BadgerGL::Rect16(BadgerGL::Point16(88, 8), 32, 32));

		Serial.println("Sanity test initialised.");
	}

	void loop()
	{
		SSD1351::Driver.clearScreen(0x0000);
		delay(500);
		SSD1351::Driver.clearScreen(0xFF00);
		delay(500);
		SSD1351::Driver.clearScreen(0x00FF);
		delay(500);
		SSD1351::Driver.clearScreenToImage(static_cast<const uint8_t*>(ScreenBufferSurface.rawPixelData()));
		delay(500);
	}
}
