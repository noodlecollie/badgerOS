#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <PlatformConfig/Platform.h>

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
		const PlatformConfig::ConfigData& configData = configInstance.data();

		Serial.begin(configData.serialConfig->baudRate);
		Serial.println("Sanity test initialised.");
	}

	void loop()
	{
	}
}
