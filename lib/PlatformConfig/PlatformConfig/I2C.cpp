#include "I2C.h"
#include <Arduino.h>

namespace PlatformConfig
{
	static inline void setPinMode(int8_t pin, uint8_t mode)
	{
		if ( pin >= 0 )
		{
			pinMode(pin, mode);
		}
	}

	void i2cSetup(const I2CConfig& config)
	{
		setPinMode(config.dataPin, INPUT_PULLUP);
		setPinMode(config.clockPin, PULLUP);
	}
}
