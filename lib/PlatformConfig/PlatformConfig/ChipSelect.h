#pragma once

#include <cstdint>

namespace PlatformConfig
{
	struct ChipSelectConfig
	{
		int8_t oledScreenCSPin;
	};

	void chipSelectSetup(const ChipSelectConfig& config);
}
