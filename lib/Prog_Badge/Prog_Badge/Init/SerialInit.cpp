#include <Arduino.h>
#include "SerialInit.h"

namespace Badge
{
	void serialInit(const PlatformConfig::SerialConfig& config)
	{
		Serial.begin(config.baudRate);
	}
}
