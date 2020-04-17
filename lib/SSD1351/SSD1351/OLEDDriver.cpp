#include <algorithm>
#include <Arduino.h>
#include <SPI.h>
#include <CoreUtil/ArrayUtil.h>
#include "OLEDDriver.h"

// Note that in this file, const_cast is used to cast away constness for calls to SPI.transferBytes().
// I've checked the argument and it's not modified in the driver. They should have just made it const.
// Boooooooooooooooooooo.

namespace SSD1351
{
	OLEDDriver Driver;

	inline constexpr uint16_t toSerialBytes(uint16_t colour)
	{
		return (colour << 8) | (colour >> 8);
	}

	OLEDDriver::OLEDDriver()
	{
	}

	void OLEDDriver::initialise(const Config& cfg)
	{
		m_Config = cfg;
		m_HasConfig = true;

		setUpPins();
		defaultDeviceInit();
	}

	void OLEDDriver::writeCommand(Command cmd)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, LOW);
		SPI.transfer(static_cast<uint8_t>(cmd));
		digitalWrite(m_Config.dataCommandPin, HIGH);
	}

	void OLEDDriver::writeCommand(Command cmd, uint8_t data)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, LOW);
		SPI.transfer(static_cast<uint8_t>(cmd));
		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transfer(data);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::writeCommand(Command cmd, uint8_t data1, uint8_t data2)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, LOW);
		SPI.transfer(static_cast<uint8_t>(cmd));
		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transfer(data1);
		SPI.transfer(data2);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::writeCommand(Command cmd, uint8_t data1, uint8_t data2, uint8_t data3)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, LOW);
		SPI.transfer(static_cast<uint8_t>(cmd));
		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transfer(data1);
		SPI.transfer(data2);
		SPI.transfer(data3);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::writeCommandBytes(Command cmd, const uint8_t* data, size_t length)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, LOW);
		SPI.transfer(static_cast<uint8_t>(cmd));
		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transferBytes(const_cast<uint8_t*>(data), nullptr, length);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::writeData(uint8_t data)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transfer(data);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::writeData(uint16_t data)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transfer(data >> 8);
		SPI.transfer(data & 0xFF);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::writeData(uint32_t data)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transfer(data >> 24);
		SPI.transfer((data >> 16) & 0xFF);
		SPI.transfer((data >> 8) & 0xFF);
		SPI.transfer(data & 0xFF);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::writeDataBytes(const uint8_t* data, size_t length)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, HIGH);
		SPI.transferBytes(const_cast<uint8_t*>(data), nullptr, length);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void OLEDDriver::clearScreen(uint16_t colour)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		colour = toSerialBytes(colour);

		for ( uint32_t x = 0; x < OLED_WIDTH; ++x )
		{
			m_RowData[x] = colour;
		}

		ramAddressSection();
		writeCommand(Command::WriteRam);

		for ( uint32_t y = 0; y < OLED_HEIGHT; ++y )
		{
			writeDataBytes(reinterpret_cast<const uint8_t*>(m_RowData), sizeof(m_RowData));
		}
	}

	void OLEDDriver::clearScreenToImage(const CoreUtil::ConstBlob& data)
	{
		if ( !m_HasConfig || !data.isValid() || data.length() < OLED_RAM_SIZE_BYTES )
		{
			return;
		}

		ramAddressSection();
		writeCommand(Command::WriteRam);

		const uint16_t* cursor = reinterpret_cast<const uint16_t*>(data.constBytes());

		for ( uint32_t row = 0; row < OLED_HEIGHT; ++row )
		{
			for ( uint32_t x = 0; x < OLED_WIDTH; ++x )
			{
				m_RowData[x] = toSerialBytes(*(cursor++));
			}

			writeDataBytes(reinterpret_cast<const uint8_t*>(m_RowData), sizeof(m_RowData));
		}
	}

	void OLEDDriver::clearScreenSectionToImage(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const CoreUtil::ConstBlob& data)
	{
		if ( !m_HasConfig ||
			 !data.isValid() ||
			 x + width > OLED_WIDTH ||
			 y + height > OLED_HEIGHT )
		{
			return;
		}

		const size_t bytesToWrite = width * height * OLED_DEPTH_BYTES;

		if ( data.length() < bytesToWrite )
		{
			return;
		}

		ramAddressSection(x, y, width, height);
		writeCommand(Command::WriteRam);

		const uint16_t* cursor = reinterpret_cast<const uint16_t*>(data.constBytes());

		for ( uint32_t row = 0; row < height; ++row )
		{
			for ( uint32_t col = 0; col < width; ++col )
			{
				m_RowData[col] = toSerialBytes(*(cursor++));
			}

			writeDataBytes(reinterpret_cast<const uint8_t*>(m_RowData), width * OLED_DEPTH_BYTES);
		}
	}

	void OLEDDriver::setUpPins()
	{
		pinMode(m_Config.resetPin, OUTPUT);
		pinMode(m_Config.dataCommandPin, OUTPUT);
	}

	void OLEDDriver::defaultDeviceInit()
	{
		digitalWrite(m_Config.resetPin, LOW);
		delay(500);
		digitalWrite(m_Config.resetPin, HIGH);
		delay(500);

		writeCommand(Command::CommandLock, 0x12);
		writeCommand(Command::CommandLock, 0xB1);
		writeCommand(Command::DisplayOff);
		writeCommand(Command::NormalDisplay);
		writeCommand(Command::SetColumn, 0x00, 0x7F);
		writeCommand(Command::SetRow, 0x00, 0x7F);
		writeCommand(Command::ClockDiv, 0xF1);
		writeCommand(Command::MuxRatio, 0x7F);
		writeCommand(Command::SetRemap, 0x74);
		writeCommand(Command::StartLine, 0x00);
		writeCommand(Command::DisplayOffset, 0x00);
		writeCommand(Command::FunctionSelect, 0x01);
		writeCommand(Command::SetVSL, 0xA0, 0xB5, 0x55);
		writeCommand(Command::ContrastABC, 0xC8, 0x80, 0xC0);
		writeCommand(Command::ContrastMaster, 0x0F);
		writeCommand(Command::PreCharge, 0x32);
		writeCommand(Command::DisplayEnhance, 0xA4, 0x00, 0x00);
		writeCommand(Command::PreChargeLevel, 0x17);
		writeCommand(Command::PreCharge2, 0x01);
		writeCommand(Command::VCOMH, 0x05);
		writeCommand(Command::NormalDisplay);

		clearScreen();
		writeCommand(Command::DisplayOn);
	}

	void OLEDDriver::ramAddressSection(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
	{
		writeCommand(Command::SetColumn, x, x + width - 1);
		writeCommand(Command::SetRow, y, y + height - 1);
	}
}
