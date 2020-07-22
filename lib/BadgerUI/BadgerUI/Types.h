#pragma once

#include <cstdint>
#include <BadgerMath/Rect2D.h>
#include <BadgerMath/Vector2D.h>
#include <BadgerGL/Defs.h>

namespace BadgerUI
{
	using UIPoint = BadgerGL::Point16;
	using UIRect = BadgerGL::Rect16;
	using UIDimensions = BadgerMath::Vector2D<uint16_t>;

	enum class HAlignment
	{
		Left,
		Centre,
		Right
	};

	enum class VAlignment
	{
		Top,
		Centre,
		Bottom
	};
}
