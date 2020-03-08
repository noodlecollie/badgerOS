#include "ESP32HAL.h"
#include <ESP.h>

namespace ESP32HAL
{
	static inline void initialiseSerial(const SerialConfig& config)
	{
		Serial.begin(config.baudRate);
		Serial.flush();
	}

	HardwareSerial& Serial = ::Serial;

	void initialise(const InitConfig& config)
	{
		initialiseSerial(config.serial);
	}

	void reset()
	{
		ESP.restart();

		while ( true )
		{
			// Trap here. Should never be reached, but just in case.
		}
	}
}
