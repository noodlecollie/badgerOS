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
}
