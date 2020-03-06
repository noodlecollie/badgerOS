#pragma once

#include <Arduino.h>
#include <heltec.h>

namespace HeltecESP32WiFiKit32
{
	void initialiseHardware();
	void reset();

	extern HardwareSerial& Serial;
	extern Heltec_ESP32& Heltec;
	extern SSD1306Wire* const Display;
}
