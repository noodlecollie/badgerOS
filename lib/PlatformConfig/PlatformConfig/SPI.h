#pragma once

#include <cstdint>
#include <SPI.h>
#include <Arduino.h>

namespace PlatformConfig
{
	struct SPIConfig
	{
		enum class ClockRateMode
		{
			Divider,
			Frequency
		};

		uint8_t dataMode;
		uint8_t bitOrder;
		ClockRateMode clockMode;
		uint32_t clockValue;
	};

	struct SPIPinConfig
	{
		int8_t clockPin;
		int8_t misoPin;	// Q
		int8_t mosiPin;	// D
		int8_t writeProtectPin;
		int8_t holdPin;
	};

	static constexpr SPIConfig SPI_CONFIG_DEFAULT =
	{
		.dataMode = SPI_MODE0,
		.bitOrder = MSBFIRST,
		.clockMode = SPIConfig::ClockRateMode::Divider,
		.clockValue = SPI_CLOCK_DIV2
	};

	void spiSetup(const SPIConfig& config);
}
