#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <PlatformConfig/ConfigArgs.h>
#include <PlatformConfig/PlatformConfigObject.h>

namespace PlatformConfig
{
	void initialiseConfig(PlatformConfigObject* configObject, const ConfigArgs& args);
	const PlatformConfigObject* globalConfig();
}
