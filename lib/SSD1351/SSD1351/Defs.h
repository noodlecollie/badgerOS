#pragma once

#include <cstddef>
#include <cstdint>

namespace SSD1351
{
	static constexpr size_t OLED_WIDTH = 128;
	static constexpr size_t OLED_HEIGHT = 128;
	static constexpr size_t OLED_DEPTH_BYTES = sizeof(uint16_t);
	static constexpr size_t OLED_RAM_SIZE_BYTES = OLED_WIDTH * OLED_HEIGHT * OLED_DEPTH_BYTES;

	enum class Command : uint8_t
	{
		SetColumn = 0x15,
		SetRow = 0x75,
		WriteRam = 0x5C,
		ReadRam = 0x5D,
		SetRemap = 0xA0,
		StartLine = 0xA1,
		DisplayOffset = 0xA2,
		DisplayAllOff = 0xA4,
		DisplayAllOn = 0xA5,
		NormalDisplay = 0xA6,
		InvertDisplay = 0xA7,
		FunctionSelect = 0xAB,
		DisplayOff = 0xAE,
		DisplayOn = 0xAF,
		PreCharge = 0xB1,
		DisplayEnhance = 0xB2,
		ClockDiv = 0xB3,
		SetVSL = 0xB4,
		SetGPIO = 0xB5,
		PreCharge2 = 0xB6,
		SetGrey = 0xB8,
		UseLUT = 0xB9,
		PreChargeLevel = 0xBB,
		VCOMH = 0xBE,
		ContrastABC = 0xC1,
		ContrastMaster = 0xC7,
		MuxRatio = 0xCA,
		CommandLock = 0xFD,
		HorizontalScroll = 0x96,
		StopScroll = 0x9E,
		StartScroll = 0x9F
	};
}
