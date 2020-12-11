#pragma once

#include <cstdint>
#include <CoreUtil/TimeHelpers.h>

namespace InkyImpression
{
	class InkyDriver
	{
	public:
		struct Config
		{
			uint8_t resetPin;
			uint8_t dataCommandPin;
			uint8_t busyPin;
		};

		void initialise(const Config& cfg);
		bool isReady(CoreUtil::TimevalMs blockingTimeoutMS = 0, CoreUtil::TimevalMs delayIntervalMS = 10) const;

	private:
		void setUpPins();
		void defaultDeviceInit();
		void assertReady() const;

		Config m_Config;
		bool m_HasConfig = false;
	};

	extern InkyDriver Driver;
}
