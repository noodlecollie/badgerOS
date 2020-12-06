#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <PlatformConfig/ConfigArgs.h>
#include <PlatformConfig/ConfigData.h>

namespace PlatformConfig
{
	using ConfigInitFunc = void (*)(const ConfigArgs&, ConfigData&);

	void initialiseConfig(ConfigInitFunc factoryFunc, const ConfigArgs& args);
	const ConfigArgs& globalConfigArgs();
	const ConfigData& globalConfigData();

	template<typename T>
	static inline const T& globalConfigItem(const T* ConfigData::* configEntryPtr)
	{
		BGRS_ASSERT(configEntryPtr, "No config entry pointer was provided.");

		const ConfigData& config = globalConfigData();
		const T* configEntry = config.*configEntryPtr;

		BGRS_ASSERT(configEntry, "Specified config entry was not valid.");
		return *configEntry;
	}

	template<typename T, typename FUNC>
	static inline void initialiseSubsystem(const T* ConfigData::* configEntryPtr, const FUNC& initFunc)
	{
		BGRS_ASSERT(initFunc, "No initialisation function was provided.");

		initFunc(globalConfigItem(configEntryPtr));
	}
}
