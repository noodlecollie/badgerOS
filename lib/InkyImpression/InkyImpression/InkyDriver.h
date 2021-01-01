#pragma once

#include <cstdint>
#include <CoreUtil/TimeHelpers.h>
#include <CoreUtil/Blob.h>
#include <InkyImpression/Defs.h>

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

		// Provided data must be DISPLAY_IMAGE_SIZE_BYTES in length.
		void writeImage(const CoreUtil::ConstBlob& data);

	private:
		void setUpPins();
		void defaultDeviceInit();
		void assertReady() const;
		void setDisplayOn(bool turnOn);
		bool isReady(CoreUtil::TimevalMs blockingTimeoutMS = 0, CoreUtil::TimevalMs delayIntervalMS = 10) const;

		void writeCommand(Command cmd);
		void writeCommand(Command cmd, uint8_t data);
		void writeCommand(Command cmd, uint8_t data1, uint8_t data2);
		void writeCommand(Command cmd, uint8_t data1, uint8_t data2, uint8_t data3);
		void writeCommand(Command cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
		void writeCommandBytes(Command cmd, const uint8_t* data, size_t length);

		Config m_Config;
		bool m_HasConfig = false;
	};

	extern InkyDriver Driver;
}
