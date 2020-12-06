#include <Arduino.h>
#include "ChipSelect.h"

namespace PlatformConfig
{
	static inline void setPinMode(int8_t pin, uint8_t mode)
	{
		if ( pin >= 0 )
		{
			pinMode(pin, mode);
		}
	}

	void chipSelectSetup(const ChipSelectConfig& config)
	{
		setPinMode(config.displayCSPin, OUTPUT);
	}
}
