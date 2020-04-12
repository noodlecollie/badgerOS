#pragma once

#include "Meta/StaticImageMetadata.h"

namespace Resources
{
	namespace Missing
	{
		static constexpr size_t WIDTH = 8;
		static constexpr size_t HEIGHT = 8;

		// This may be useful for converting formats: https://stackoverflow.com/questions/8579353/convert-16bit-colour-to-32bit
		static constexpr uint16_t COL_PINK = 0b1111100000011010;
		static constexpr uint16_t COL_BLACK = 0x0000;

		static constexpr const uint16_t DATA[WIDTH * HEIGHT] =
		{
			COL_PINK, COL_PINK, COL_PINK, COL_PINK, COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK,
			COL_PINK, COL_PINK, COL_PINK, COL_PINK, COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK,
			COL_PINK, COL_PINK, COL_PINK, COL_PINK, COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK,
			COL_PINK, COL_PINK, COL_PINK, COL_PINK, COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK,
			COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK, COL_PINK, COL_PINK, COL_PINK, COL_PINK,
			COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK, COL_PINK, COL_PINK, COL_PINK, COL_PINK,
			COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK, COL_PINK, COL_PINK, COL_PINK, COL_PINK,
			COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK, COL_PINK, COL_PINK, COL_PINK, COL_PINK,
		};

		static constexpr StaticImageMetadata META =
		{
			.width = WIDTH,
			.height = HEIGHT,
			.pixelFormat = BadgerGL::PIXELFORMAT_65K,
			.isRowMajor = true,
			.data = DATA
		};
	}
}
