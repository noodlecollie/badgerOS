#include <Arduino.h>
#include "Power.h"

namespace PlatformConfig
{
	static inline void setPinMode(int8_t pin, uint8_t mode)
	{
		if ( pin >= 0 )
		{
			pinMode(pin, mode);
		}
	}

	void powerSetup(const PowerConfig& config)
	{
		setPinMode(config.batteryLevelPin, INPUT_PULLUP);
		setPinMode(config.externalPowerSensePin, INPUT);
	}
}
