#pragma once

#include <HardwareSerial.h>
#include "InitConfig.h"

namespace ESP32HAL
{
	extern HardwareSerial& Serial;

	void initialise(const InitConfig& config);
	void reset();
}
