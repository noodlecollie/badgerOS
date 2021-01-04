#include <CoreUtil/BgrsAssert.h>
#include "Platform.h"

namespace PlatformConfig
{
	static ConfigArgs LocalConfigArgs;
	static const PlatformConfigObject* LocalConfigObject = nullptr;

	void initialiseConfig(PlatformConfigObject* configObject, const ConfigArgs& args)
	{
		BGRS_ASSERT(configObject, "Config object was not valid.");

		LocalConfigArgs = args;
		LocalConfigObject = configObject;
		configObject->initialise(args);
	}

	const PlatformConfigObject* globalConfig()
	{
		return LocalConfigObject;
	}
}
