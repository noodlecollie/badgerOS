#include <Arduino.h>
#include <CoreUtil/BgrsAssert.h>
#include <InkyImpression/InkyDriver.h>

namespace InkyImpression
{
	// 15 second wait for the display to be ready, as per the Python Inky drivers.
	static constexpr CoreUtil::TimevalMs DEFAULT_BUSY_WAIT_TIME = 15000;

	InkyDriver Driver;

	void InkyDriver::initialise(const Config& cfg)
	{
		m_Config = cfg;
		m_HasConfig = true;

		setUpPins();
		defaultDeviceInit();
	}

	void InkyDriver::setUpPins()
	{
		pinMode(m_Config.resetPin, OUTPUT);
		pinMode(m_Config.dataCommandPin, OUTPUT);
		pinMode(m_Config.busyPin, INPUT);
	}

	void InkyDriver::defaultDeviceInit()
	{
		digitalWrite(m_Config.resetPin, LOW);
		delay(100);
		digitalWrite(m_Config.resetPin, HIGH);
		delay(100);

		assertReady();

		// TODO: Continue
	}

	bool InkyDriver::isReady(CoreUtil::TimevalMs blockingTimeoutMS, CoreUtil::TimevalMs delayIntervalMS) const
	{
		bool ready = digitalRead(m_Config.busyPin) == LOW;

		if ( blockingTimeoutMS < 1 )
		{
			return ready;
		}

		const CoreUtil::TimevalMs startTime = millis();

		do
		{
			delay(delayIntervalMS);
			ready = digitalRead(m_Config.busyPin) == LOW;
		}
		while ( !ready && (blockingTimeoutMS == CoreUtil::DURATION_INFINITE || millis() - startTime < blockingTimeoutMS) );

		return ready;
	}

	void InkyDriver::assertReady() const
	{
		const bool displayReady = isReady(DEFAULT_BUSY_WAIT_TIME);

		if ( !displayReady )
		{
			Serial.printf("InkyDriver: Timeout waiting for display to be ready! (%.2fs)\r\n", static_cast<float>(DEFAULT_BUSY_WAIT_TIME) / 1000.0f);
		}

		BGRS_ASSERT(displayReady, "Timeout waiting for display to be ready!");
	}
}
