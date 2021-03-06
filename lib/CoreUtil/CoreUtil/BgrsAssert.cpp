#include <Arduino.h>
#include <Esp.h>
#include "BgrsAssert.h"

#define ASSERT_LED_ITERATIONS_PER_FLASH 2
#define ASSERT_LED_FLASHES_PER_SEC 8
#define ASSERT_LED_ITERATIONS_PER_SEC (ASSERT_LED_ITERATIONS_PER_FLASH * ASSERT_LED_FLASHES_PER_SEC)

#ifdef HAS_DEBUG_LED
#define SET_DEBUG_LED(on) digitalWrite(LED, (on) ? HIGH : LOW)
#else
#define SET_DEBUG_LED(...)
#endif

#ifdef BGRS_DEBUG
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
			Serial.printf("\r\n** ASSERTION FAILED: \"%s\" @ %s:%d. Message: %s\r\n", conditionStr, file, line, desc);
			Serial.flush();

			bool ledOn = false;

			for ( int iteration = 0; ASSERT_LED_FLASH_COND(iteration); ++iteration )
			{
				ledOn = !ledOn;
				SET_DEBUG_LED(ledOn);

				delay(1000 / ASSERT_LED_ITERATIONS_PER_SEC);
			}

#ifndef DEBUG
			ESP.restart();
#endif
		}
	}
}
