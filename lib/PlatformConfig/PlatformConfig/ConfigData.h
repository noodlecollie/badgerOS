#pragma once

#include <SSD1351/OLEDDriver.h>
#include <PlatformConfig/Serial.h>
#include <PlatformConfig/SPI.h>
#include <PlatformConfig/ChipSelect.h>
#include <PlatformConfig/Power.h>

namespace PlatformConfig
{
	struct ConfigData
	{
		const SSD1351::OLEDDriver::Config* ssd1351Config;
		const SerialConfig* serialConfig;
		const SPIConfig* spiConfig;
		const SPIPinConfig* spiPinConfig;
		const ChipSelectConfig* chipSelectConfig;
		const PowerConfig* powerConfig;
	};
}
