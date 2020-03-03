#include "WiFiKit32.h"
#include "heltec.h"
#include "ESP.h"

namespace WifiKit32
{
	// Most of these helper functions were taken from the Heltec library begin() function,
	// and modified so as not to include the unnecessary Chinese-English log messages.
	static inline void initialiseSerial()
	{
		// TODO: Make baud rate configurable one day?
		Serial.begin(115200);
		Serial.flush();
	}

	static inline void initialiseOLED()
	{
		// TODO: Make font configurable one day?
		Heltec.display->init();
		Heltec.display->flipScreenVertically();
		Heltec.display->setFont(ArialMT_Plain_10);
		Heltec.display->clear();
	}

	HardwareSerial& Serial = ::Serial;
	Heltec_ESP32& Heltec = ::Heltec;
	SSD1306Wire* const Display = ::Heltec.display;

	void initialiseHardware()
	{
		pinMode(LED, OUTPUT);
		digitalWrite(LED, LOW);

		pinMode(KEY_BUILTIN, INPUT_PULLUP);

		initialiseSerial();
		initialiseOLED();
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
