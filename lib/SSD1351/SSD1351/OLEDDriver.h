#pragma once

#include <cstdint>
#include <cstddef>
#include <CoreUtil/Blob.h>
#include "Defs.h"

namespace SSD1351
{
	// Base driver for SSD1351 OLED screen. Assumes 4-wire SPI communications.
	// All commands that communicate with the OLED screen assume that the chip
	// select line is active - this driver does not manage this line.
	class OLEDDriver
	{
	public:
		struct Config
		{
			uint8_t resetPin;
			uint8_t dataCommandPin;
		};

		OLEDDriver();

		// This function uses blocking waits to reset the OLED.
		void initialise(const Config& cfg);

		void writeCommand(Command cmd);
		void writeCommand(Command cmd, uint8_t data);
		void writeCommand(Command cmd, uint8_t data1, uint8_t data2);
		void writeCommand(Command cmd, uint8_t data1, uint8_t data2, uint8_t data3);
		void writeCommandBytes(Command cmd, const uint8_t* data, size_t length);

		void writeData(uint8_t data);
		void writeData(uint16_t data);
		void writeData(uint32_t data);
		void writeDataBytes(const uint8_t* data, size_t length);

		void clearScreen(uint16_t colour = 0x0000);

		// If the data is not at least OLED_RAM_SIZE_BYTES in length, this function will do nothing.
		void writeImage(const CoreUtil::ConstBlob& data);

		// If the data is not at least (width * height * OLED_DEPTH_BYTES) in length, or the defined rectangle is not within
		// the bounds of the screen, this function will do nothing.
		void writeImage(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const CoreUtil::ConstBlob& data);

	private:
		void setUpPins();
		void defaultDeviceInit();

		// Assumes that all values are valid for the screen dimensions.
		void ramAddressSection(uint8_t x = 0, uint8_t y = 0, uint8_t width = OLED_WIDTH, uint8_t height = OLED_HEIGHT);

		Config m_Config;
		bool m_HasConfig = false;
		uint16_t m_RowData[SSD1351::OLED_WIDTH];
	};

	extern OLEDDriver Driver;
}
