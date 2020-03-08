#include <Arduino.h>
#include "Assert.h"

#define ASSERT_LED_ITERATIONS_PER_FLASH 2
#define ASSERT_LED_FLASHES_PER_SEC 8
#define ASSERT_LED_ITERATIONS_PER_SEC (ASSERT_LED_ITERATIONS_PER_FLASH * ASSERT_LED_FLASHES_PER_SEC)

#ifdef DEBUG
// Flash indefinitely
#define ASSERT_LED_FLASH_COND(iteration) true
#else
// Flash for 2 seconds
#define ASSERT_LED_FLASH_COND(iteration) ((iteration) < (2 * ASSERT_LED_ITERATIONS_PER_SEC))
#endif

namespace CoreUtil
{
	void assertFunc(bool condition, const char* conditionStr, const char* desc, const char* file, int line)
	{
		if ( !condition )
		{
			Serial.printf("** ASSERTION FAILED: %s:%d %s - %s\n", file, line, conditionStr, desc);
			Serial.flush();

			bool ledOn = false;

			for ( int iteration = 0; ASSERT_LED_FLASH_COND(iteration); ++iteration )
			{
				ledOn = !ledOn;
				digitalWrite(LED, ledOn ? HIGH : LOW);

				delay(1000 / ASSERT_LED_ITERATIONS_PER_SEC);
			}

#ifndef DEBUG
			HeltecESP32WifiKit32::reset();
#endif
		}
	}
}
