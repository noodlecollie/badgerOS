#include <Arduino.h>
#include <CoreUtil/BgrsAssert.h>
#include <InkyImpression/InkyDriver.h>
#include <SPI.h>

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

		{
			const uint16_t width = DISPLAY_WIDTH;
			const uint16_t height = DISPLAY_HEIGHT;

			writeCommand(Command::TCONResolution,
						 (height & 0x0300) >> 8,
						 height & 0x00FF,
						 (width& 0x0100) >> 8,
						 width & 0x00FF);
		}

		// Panel Setting
		// 0b11000000 = Resolution select, 0b00 = 640x480, our panel is 0b11 = 600x448
		// 0b00100000 = LUT selection, 0 = ext flash, 1 = registers, we use ext flash
		// 0b00010000 = Ignore
		// 0b00001000 = Gate scan direction, 0 = down, 1 = up (default)
		// 0b00000100 = Source shift direction, 0 = left, 1 = right (default)
		// 0b00000010 = DC-DC converter, 0 = off, 1 = on
		// 0b00000001 = Soft reset, 0 = Reset, 1 = Normal (Default)
		writeCommand(Command::PanelSetting, 0b11101111, 0x08);

		writeCommand(Command::PowerSetting,
					 (0x06 << 3) | // ??? - not documented in UC8159 datasheet
					 (0x01 << 2) | // SOURCE_INTERNAL_DC_DC
					 (0x01 << 1) | // GATE_INTERNAL_DC_DC
					 (0x01),       // LV_SOURCE_INTERNAL_DC_DC
					 0x00,         // VGx_20V
					 0x23,         // UC8159_7C
					 0x23          // UC8159_7C
		);

		// Set the PLL clock frequency to 50Hz
		// 0b11000000 = Ignore
		// 0b00111000 = M
		// 0b00000111 = N
		// PLL = 2MHz * (M / N)
		// PLL = 2MHz * (7 / 4)
		// PLL = 2,800,000 ???
		writeCommand(Command::PLLControl, 0x3C); // 0b00111100

		// Not sure why this is named after a temperature sensor,
		// but apparently it's used for sending colour data to the display.
		writeCommand(Command::TemperatureSensorCalibration, 0x00);

		// VCOM and Data Interval setting
		// 0b11100000 = Vborder control (0b001 = LUTB voltage)
		// 0b00010000 = Data polarity
		// 0b00001111 = Vcom and data interval (0b0111 = 10, default)
		writeCommand(Command::VcomAndDataIntervalSetting, 0x37); // 0b00110111

		// Gate/Source non-overlap period
		// 0b11110000 = Source to Gate (0b0010 = 12nS, default)
		// 0b00001111 = Gate to Source
		writeCommand(Command::TCONSetting, 0x22); // 0b00100010

		// Disable external flash
		writeCommand(Command::SPIFlashControl, 0x00);

		// UC8159_7C
		writeCommand(Command::PowerSaving, 0xAA);

		// Power off sequence
		// 0b00110000 = power off sequence of VDH and VDL, 0b00 = 1 frame (default)
		// All other bits ignored?
		writeCommand(Command::PowerOffSequenceSetting, 0x00); // PFS_1_FRAME

		// Remove this once we've tested:
		writeCommand(Command::DataStartTransmission1);
		writeTestScreenData();
		assertReady();

		setDisplayOn(true);
		assertReady();

		writeCommand(Command::DisplayRefresh);
		assertReady();

		setDisplayOn(false);
		assertReady();
	}

	bool InkyDriver::isReady(CoreUtil::TimevalMs blockingTimeoutMS, CoreUtil::TimevalMs delayIntervalMS) const
	{
		bool ready = digitalRead(m_Config.busyPin) == HIGH;

		if ( blockingTimeoutMS < 1 )
		{
			return ready;
		}

		const CoreUtil::TimevalMs startTime = millis();

		do
		{
			delay(delayIntervalMS);
			ready = digitalRead(m_Config.busyPin) == HIGH;
		}
		while ( !ready && (blockingTimeoutMS == CoreUtil::DURATION_INFINITE || millis() - startTime < blockingTimeoutMS) );

		return ready;
	}

	void InkyDriver::setDisplayOn(bool turnOn)
	{
		writeCommand(turnOn ? Command::PowerOn : Command::PowerOff);
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

	void InkyDriver::writeCommand(Command cmd)
	{
		if ( !m_HasConfig )
		{
			return;
		}

		digitalWrite(m_Config.dataCommandPin, LOW);
		SPI.transfer(static_cast<uint8_t>(cmd));
		digitalWrite(m_Config.dataCommandPin, HIGH);
	}

	void InkyDriver::writeCommand(Command cmd, uint8_t data)
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

	void InkyDriver::writeCommand(Command cmd, uint8_t data1, uint8_t data2)
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

	void InkyDriver::writeCommand(Command cmd, uint8_t data1, uint8_t data2, uint8_t data3)
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

	void InkyDriver::writeCommand(Command cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
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
		SPI.transfer(data4);
		digitalWrite(m_Config.dataCommandPin, LOW);
	}

	void InkyDriver::writeCommandBytes(Command cmd, const uint8_t* data, size_t length)
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

	void InkyDriver::writeTestScreenData()
	{
		digitalWrite(m_Config.dataCommandPin, HIGH);

		for ( size_t rowIndex = 0; rowIndex < DISPLAY_HEIGHT; ++rowIndex )
		{
			for ( size_t colIndex = 0; colIndex < DISPLAY_WIDTH / 2; ++colIndex )
			{
				const uint8_t col = (rowIndex % 8);
				SPI.transfer((col << 4) | col);
			}
		}

		digitalWrite(m_Config.dataCommandPin, LOW);
	}
}
