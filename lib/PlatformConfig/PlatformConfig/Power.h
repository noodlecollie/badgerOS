#pragma once

#include <cstdint>

namespace PlatformConfig
{
	struct PowerConfig
	{
		int8_t batteryLevelPin;
		int8_t externalPowerSensePin;
	};

	void powerSetup(const PowerConfig& config);
}
