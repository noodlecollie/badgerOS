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
	static inline const T& globalConfigItem(const T* Config::* configEntryPtr)
	{
		BGRS_ASSERT(configEntryPtr, "No config entry pointer was provided.");

		const Config& config = globalConfig();
		const T* configEntry = config.*configEntryPtr;

		BGRS_ASSERT(configEntry, "Specified config entry was not valid.");
		return *configEntry;
	}

	template<typename T, typename FUNC>
	static inline void initialiseSubsystem(const T* Config::* configEntryPtr, const FUNC& initFunc)
	{
		BGRS_ASSERT(initFunc, "No initialisation function was provided.");

		initFunc(globalConfigItem(configEntryPtr));
	}
}
