#pragma once

#include <PlatformConfig/ConfigArgs.h>

namespace WifiSoftAP
{
	void getPlatformConfigArgs(PlatformConfig::ConfigArgs& args);
	void setup();
	void loop();
}
