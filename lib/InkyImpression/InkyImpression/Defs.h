#pragma once

#include <cstddef>
#include <cstdint>

namespace InkyImpression
{
	static constexpr size_t DISPLAY_WIDTH = 600;
	static constexpr size_t DISPLAY_HEIGHT = 448;

	static constexpr uint8_t COL_BLACK = 0;
	static constexpr uint8_t COL_WHITE = 1;
	static constexpr uint8_t COL_GREEN = 2;
	static constexpr uint8_t COL_BLUE = 3;
	static constexpr uint8_t COL_RED = 4;
	static constexpr uint8_t COL_YELLOW = 5;
	static constexpr uint8_t COL_ORANGE = 6;
	static constexpr uint8_t COL_CLEAN = 7;
	static constexpr uint8_t COL_MASK = 0b111;

	enum class Command : uint8_t
	{
		PanelSetting = 0x00,
		PowerSetting = 0x01,
		PowerOff = 0x02,
		PowerOffSequenceSetting = 0x03,
		PowerOn = 0x04,
		BoosterSoftStart = 0x06,
		DeepSleep = 0x07,
		DataStartTransmission1 = 0x10,
		DataStop = 0x11,
		DisplayRefresh = 0x12,
		ImageProcessCommand = 0x13,
		VCOMLUT = 0x20,
		LUTBlue = 0x21,
		LUTWhite = 0x22,
		LUTGrey1 = 0x23,
		LUTGrey2 = 0x24,
		LUTRed0 = 0x25,
		LUTRed1 = 0x26,
		LUTRed2 = 0x27,
		LUTRed3 = 0x28,
		LUTXON = 0x29,
		PLLControl = 0x30,
		TemperatureSensorCommand = 0x40,
		TemperatureSensorCalibration = 0x41,
		TemperatureSensorWrite = 0x42,
		TemperatureSensorRead = 0x43,
		VcomAndDataIntervalSetting = 0x50,
		LowerPowerDetection = 0x51,
		TCONSetting = 0x60,
		TCONResolution = 0x61,
		SPIFlashControl = 0x65,
		Revision = 0x70,
		GetStatus = 0x71,
		AutoMeasurementVcom = 0x80,
		ReadVcomValue = 0x81,
		VCMDCSettings = 0x82,
		PowerSaving = 0xE3
	};
}
