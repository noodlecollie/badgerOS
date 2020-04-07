#include <CoreUtil/BgrsAssert.h>
#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <SSD1351/CustomDriver/OLEDDriver.h>

#include "SanityTest.h"

namespace SanityTest
{
	static SSD1351::OLEDDriver driver;

	void setup(PlatformConfig::ConfigFactoryFunc configFunc)
	{
		BGRS_ASSERT(configFunc, "Config factory function is required.");

		PlatformConfig::Config config;
		configFunc(config);

		BGRS_ASSERT(config.ssd1351Config, "SSD1351 config is required.");
		BGRS_ASSERT(config.serialConfig, "Serial config is required.");
		BGRS_ASSERT(config.spiConfig, "SPI config is required.");

		Serial.begin(config.serialConfig->baudRate);

		Serial.printf("Sanity test initialising...\n");
		Serial.printf("\n");

		Serial.printf("=== Serial configuration:\n");
		Serial.printf("      Baud rate: %u\n", config.serialConfig->baudRate);
		Serial.printf("\n");

		Serial.printf("=== SSD1351 configuration:\n");
		Serial.printf("    Chip select: %u\n", config.ssd1351Config->chipSelectPin);
		Serial.printf("          Reset: %u\n", config.ssd1351Config->resetPin);
		Serial.printf("   Data/command: %u\n", config.ssd1351Config->dataCommandPin);
		Serial.printf("          Clock: %u\n", config.ssd1351Config->clockPin);
		Serial.printf("        Data in: %u\n", config.ssd1351Config->dataInPin);
		Serial.printf("\n");

		Serial.printf("=== SPI configuration:\n");
		Serial.printf("      Data mode: %u\n", config.spiConfig->dataMode);
		Serial.printf("      Bit order: %u\n", config.spiConfig->bitOrder);
		Serial.printf("  Clock divider: %u\n", config.spiConfig->clockDivider);
		Serial.printf("\n");

		SPI.setDataMode(config.spiConfig->dataMode);
		SPI.setBitOrder(config.spiConfig->bitOrder);
		SPI.setClockDivider(config.spiConfig->clockDivider);
		SPI.begin(config.ssd1351Config->clockPin, -1, config.ssd1351Config->dataInPin, -1);

		digitalWrite(config.ssd1351Config->chipSelectPin, LOW);
		driver.initialise(*config.ssd1351Config);
		Serial.println("Sanity test initialised.");
	}

	void loop()
	{
		driver.clearScreen(0x0000);
		delay(500);
		driver.clearScreen(0xFF00);
		delay(500);
		driver.clearScreen(0x00FF);
		delay(500);
	}
}
