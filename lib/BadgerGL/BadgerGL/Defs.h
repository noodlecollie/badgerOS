#pragma once

#include <cstdint>
#include <BadgerMath/Vector2D.h>
#include <BadgerMath/Rect2D.h>

namespace BadgerGL
{
	using Point16 = BadgerMath::Vector2D<int16_t>;
	using Rect16 = BadgerMath::Rect2D<int16_t>;

	using UPoint16 = BadgerMath::Vector2D<uint16_t>;
	using URect16 = BadgerMath::Rect2D<uint16_t>;

	enum class ShapeDrawStyle
	{
		Outline,		// Only outline of shape is drawn in primary colour.
		Filled,			// Shape is filled with primary colour.
		FilledOutline	// Outline is drawn in primary colour, and interior is filled with secondary colour.
	};

	static constexpr uint8_t bitDepthToByteDepth(uint8_t bitDepth)
	{
		return (bitDepth + 7) / 8;
	}

	static constexpr size_t maskedDataSizeForDimensions(uint16_t width, uint16_t height)
	{
		return height * bitDepthToByteDepth(width);
	}

	// Single-channel colour.
	static constexpr uint8_t col8To5(uint8_t col)
	{
		return static_cast<uint8_t>((static_cast<uint32_t>(col) * 31) / 255);
	}

	// Single-channel colour.
	static constexpr uint8_t col8To6(uint8_t col)
	{
		return static_cast<uint8_t>((static_cast<uint32_t>(col) * 63) / 255);
	}

	// Converts 0RGB[8:8:8:8] to RGB[5:6:5].
	static constexpr uint16_t col24To16(uint32_t col)
	{
		// If this were not a constexpr function, it would look something like this:

		// uint8_t red = col8To5((col & 0x00FF0000) >> 16);
		// uint8_t green = col8To6((col & 0x0000FF00) >> 8);
		// uint8_t blue = col8To5(col & 0x000000FF);

		// return
		// 	(static_cast<uint16_t>(red) << 11) |
		// 	(static_cast<uint16_t>(green) << 5) |
		// 	static_cast<uint16_t>(blue);

		// As a constexpr one-liner, this becomes:

		return
			(static_cast<uint16_t>(col8To5((col & 0x00FF0000) >> 16)) << 11) |
			(static_cast<uint16_t>(col8To6((col & 0x0000FF00) >> 8)) << 5) |
			 static_cast<uint16_t>(col8To5(col & 0x000000FF));
	}

	// Converts RGB0[8:8:8:8] to RGB[5:6:5].
	static constexpr uint16_t col32To16(uint32_t col)
	{
		return col24To16(col >> 8);
	}
}
