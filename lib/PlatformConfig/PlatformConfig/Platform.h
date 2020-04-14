#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <SSD1351/CustomDriver/OLEDDriver.h>
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

	template<typename T>
	static inline void initialiseSubsystem(const T* Config::* configEntryPtr, void (*initFunc)(const T&))
	{
		BGRS_ASSERT(configEntryPtr, "No config entry pointer was provided.");
		BGRS_ASSERT(initFunc, "No initialisation function was provided.");

		const Config& config = globalConfig();
		const T* configEntry = config.*configEntryPtr;

		BGRS_ASSERT(configEntry, "Specified config entry was not valid.");

		initFunc(*configEntry);
	}
}
