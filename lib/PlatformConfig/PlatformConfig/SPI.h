#pragma once

#include <cstdint>
#include <SPI.h>
#include <Arduino.h>

namespace PlatformConfig
{
	struct SPIConfig
	{
		uint8_t dataMode;
		uint8_t bitOrder;
		uint32_t clockDivider;
	};

	static constexpr SPIConfig SPI_CONFIG_DEFAULT =
	{
		.dataMode = SPI_MODE0,
		.bitOrder = MSBFIRST,
		.clockDivider = SPI_CLOCK_DIV2
	};
}
