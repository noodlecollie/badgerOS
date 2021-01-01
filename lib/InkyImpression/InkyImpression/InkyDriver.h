#pragma once

#include <cstdint>
#include <CoreUtil/BgrsAssert.h>
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

		// Write the image scanning from left to right, top to bottom.
		// For each pixel, the provided callback is called to obtain the colour.
		template<typename CB>
		void writeImagePixelwise(const CB& callback)
		{
			BGRS_ASSERT(callback, "Callback must be valid.");

			beginWriteImage();

			for ( uint32_t pixelIndex = 0; pixelIndex < DISPLAY_IMAGE_SIZE_BYTES; pixelIndex += 2 )
			{
				writeImagePixelPair(callback(pixelIndex), callback(pixelIndex + 1));
			}

			assertReady();
			refreshDisplay();
		}

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

		void beginWriteImage();
		void writeImagePixelPair(uint8_t pixel0, uint8_t pixel1);
		void refreshDisplay();

		Config m_Config;
		bool m_HasConfig = false;
	};

	extern InkyDriver Driver;
}
