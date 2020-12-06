#pragma once

#include <PlatformConfig/Serial.h>
#include <PlatformConfig/SPI.h>
#include <PlatformConfig/ChipSelect.h>
#include <PlatformConfig/Power.h>

#include <SSD1351/OLEDDriver.h>
#include <InkyImpression/Driver.h>

namespace PlatformConfig
{
	struct ConfigData
	{
		union
		{
			const SSD1351::OLEDDriver::Config* ssd1351;
			const InkyImpression::Driver::Config* inkyImpression;
		} displayConfig;

		const SerialConfig* serialConfig;
		const SPIConfig* spiConfig;
		const SPIPinConfig* spiPinConfig;
		const ChipSelectConfig* chipSelectConfig;
		const PowerConfig* powerConfig;
	};
}
