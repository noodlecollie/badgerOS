#pragma once

#include <cstdint>

namespace PlatformConfig
{
	// TODO: Add more of the serial configuration options to this in future.
	struct SerialConfig
	{
		uint32_t baudRate;
	};

	static constexpr SerialConfig SERIAL_CONFIG_DEFAULT =
	{
		.baudRate = 115200
	};
}
