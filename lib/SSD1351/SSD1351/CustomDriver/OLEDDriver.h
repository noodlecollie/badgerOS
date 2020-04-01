#pragma once

#include <cstdint>
#include <cstddef>
#include "Defs.h"

namespace SSD1351
{
	// Base driver for SSD1351 OLED screen.
	// Assumes 4-wire SPI communications.
	class OLEDDriver
	{
	public:
		struct Config
		{
			uint8_t chipSelectPin = 0;
			uint8_t resetPin = 0;
			uint8_t dataCommandPin = 0;
			uint8_t clockPin = 0;
			uint8_t dataInPin = 0;

			inline Config& operator =(const Config& other) = default;
		};

		OLEDDriver();

		// These functions assume that the chip select pin is low.

		// This function uses blocking waits to reset the OLED,
		// and assumes that the pin modes have already been set up.
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

	private:
		void defaultDeviceInit();
		void ramAddress();

		Config m_Config;
		bool m_HasConfig = false;
	};
}
