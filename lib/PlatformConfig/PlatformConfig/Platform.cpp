#include <CoreUtil/BgrsAssert.h>
#include "Platform.h"

namespace PlatformConfig
{
	static Config LocalConfig;

	void initialiseConfig(ConfigFactoryFunc factoryFunc)
	{
		BGRS_ASSERT(factoryFunc, "Config factory function was not valid.");
		factoryFunc(LocalConfig);
	}

	const Config& globalConfig()
	{
		return LocalConfig;
	}
}
