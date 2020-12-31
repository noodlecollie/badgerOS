#pragma once

#pragma once

#include <cstdint>
#include <Arduino.h>

namespace PlatformConfig
{
	struct I2CConfig
	{
		uint8_t dataPin;
		uint8_t clockPin;
	};

	void i2cSetup(const I2CConfig& config);
}
