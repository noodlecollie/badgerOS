#include <CoreUtil/BgrsAssert.h>
#include "Platform.h"

namespace PlatformConfig
{
	static ConfigArgs LocalConfigArgs;
	static ConfigData LocalConfigData;

	void initialiseConfig(ConfigInitFunc initFunc, const ConfigArgs& args)
	{
		BGRS_ASSERT(initFunc, "Config init function was not valid.");

		LocalConfigArgs = args;
		initFunc(LocalConfigArgs, LocalConfigData);
	}

	const ConfigArgs& globalConfigArgs()
	{
		return LocalConfigArgs;
	}

	const ConfigData& globalConfigData()
	{
		return LocalConfigData;
	}
}
