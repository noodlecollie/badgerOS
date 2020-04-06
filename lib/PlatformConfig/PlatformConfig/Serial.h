#pragma once

#include <cstdint>

namespace PlatformConfig
{
	struct SerialConfig
	{
		uint32_t baudRate;
	};

	static constexpr SerialConfig SERIAL_CONFIG_DEFAULT =
	{
		.baudRate = 115200
	};
}
