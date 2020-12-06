#pragma once

#include <cstdint>

namespace PlatformConfig
{
	struct ChipSelectConfig
	{
		int8_t displayCSPin;
	};

	void chipSelectSetup(const ChipSelectConfig& config);
}
