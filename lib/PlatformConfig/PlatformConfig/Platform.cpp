#include <CoreUtil/BgrsAssert.h>
#include "Platform.h"

namespace PlatformConfig
{
	static ConfigArgs LocalConfigArgs;
	static ConfigData LocalConfigData;
	static ConfigInstance LocalInstance(LocalConfigArgs, LocalConfigData);

	void initialiseConfig(ConfigInitFunc initFunc, const ConfigArgs& args)
	{
		BGRS_ASSERT(initFunc, "Config init function was not valid.");

		LocalConfigArgs = args;
		initFunc(LocalConfigArgs, LocalConfigData);
	}

	const ConfigInstance& globalConfig()
	{
		return LocalInstance;
	}
}
