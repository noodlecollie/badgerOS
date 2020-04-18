#pragma once

#include <BadgerGL/BitmapMask.h>
#include <BadgerGL/Defs.h>

namespace Resources
{
	namespace ChequerboardMask
	{
		static constexpr size_t WIDTH = 8;
		static constexpr size_t HEIGHT = 8;

		static constexpr const uint8_t DATA[BadgerGL::maskedDataSizeForDimensions(WIDTH, HEIGHT)] =
		{
			0b01010101,
			0b10101010,
			0b01010101,
			0b10101010,
			0b01010101,
			0b10101010,
			0b01010101,
			0b10101010,
		};

		static constexpr BadgerGL::BitmapMask BITMAP(WIDTH, HEIGHT, DATA);
	}
}
