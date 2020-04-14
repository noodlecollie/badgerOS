#pragma once

#include "SSD1351/CustomDriver/OLEDDriver.h"
#include "Serial.h"
#include "SPI.h"
#include "ChipSelect.h"

namespace PlatformConfig
{
	struct Config
	{
		const SSD1351::OLEDDriver::Config* ssd1351Config;
		const SerialConfig* serialConfig;
		const SPIConfig* spiConfig;
		const SPIPinConfig* spiPinConfig;
		const ChipSelectConfig* chipSelectConfig;
	};

	using ConfigFactoryFunc = void (*)(Config&);

	void initialiseConfig(ConfigFactoryFunc factoryFunc);
	const Config& globalConfig();
}
