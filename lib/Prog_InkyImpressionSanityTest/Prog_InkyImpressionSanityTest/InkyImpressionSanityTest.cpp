#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <CoreUtil/BgrsAssert.h>
#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>

#include "InkyImpressionSanityTest.h"

namespace InkyImpressionSanityTest
{
	void getPlatformConfigArgs(PlatformConfig::ConfigArgs& args)
	{
		args.display = PlatformConfig::DisplayType::InkyImpression;
	}

	void setup()
	{
		const PlatformConfig::ConfigInstance& configInstance = PlatformConfig::globalConfig();
		const PlatformConfig::ConfigArgs& configArgs = configInstance.args();
		const PlatformConfig::ConfigData& configData = configInstance.data();

		BGRS_ASSERT(configData.serialConfig, "Serial config is required.");
		Serial.begin(configData.serialConfig->baudRate);

		BGRS_ASSERT(configArgs.display == PlatformConfig::DisplayType::InkyImpression, "Inky Impression display must be used.");
		BGRS_ASSERT(configInstance.inkyImpressionConfig(), "Inky Impression config is required.");
		BGRS_ASSERT(configData.spiConfig, "SPI config is required.");
		BGRS_ASSERT(configData.spiPinConfig, "SPI pin config is required.");
		BGRS_ASSERT(configData.chipSelectConfig, "Chip select config is required.");

		Serial.printf("Sanity test initialising...\r\n");
		Serial.printf("Version %s\r\n", PlatformConfig::Versions::VERSION_STRING_FULL);
		Serial.printf("\r\n");

		Serial.printf("=== Chip select configuration ===\r\n");
		Serial.printf("              OLED: %u\r\n", configData.chipSelectConfig->displayCSPin);
		Serial.printf("\r\n");

		Serial.printf("=== Serial configuration ===\r\n");
		Serial.printf("         Baud rate: %u\r\n", configData.serialConfig->baudRate);
		Serial.printf("\r\n");

		Serial.printf("=== InkyImpression configuration ===\r\n");
		Serial.printf("             Reset: %u\r\n", configInstance.inkyImpressionConfig()->resetPin);
		Serial.printf("      Data/command: %u\r\n", configInstance.inkyImpressionConfig()->dataCommandPin);
		Serial.printf("              Busy: %u\r\n", configInstance.inkyImpressionConfig()->busyPin);
		Serial.printf("\r\n");

		Serial.printf("=== SPI configuration ===\r\n");
		Serial.printf("         Data mode: %u\r\n", configData.spiConfig->dataMode);
		Serial.printf("         Bit order: %u\r\n", configData.spiConfig->bitOrder);
		Serial.printf("     Clock divider: %u\r\n", configData.spiConfig->clockDivider);
		Serial.printf("         Clock pin: %u\r\n", configData.spiPinConfig->clockPin);
		Serial.printf("          MISO pin: %u\r\n", configData.spiPinConfig->misoPin);
		Serial.printf("          MOSI pin: %u\r\n", configData.spiPinConfig->mosiPin);
		Serial.printf(" Write protect pin: %u\r\n", configData.spiPinConfig->writeProtectPin);
		Serial.printf("          Hold pin: %u\r\n", configData.spiPinConfig->holdPin);
		Serial.printf("\r\n");

		PlatformConfig::chipSelectSetup(*configData.chipSelectConfig);
		PlatformConfig::spiSetup(*configData.spiConfig);

		SPI.begin(configData.spiPinConfig->clockPin,
				  configData.spiPinConfig->misoPin,
				  configData.spiPinConfig->mosiPin,
				  configData.chipSelectConfig->displayCSPin);

		InkyImpression::Driver.initialise(*configInstance.inkyImpressionConfig());

		Serial.println("Sanity test initialised.");
	}

	void loop()
	{
	}
}
