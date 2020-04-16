#pragma once

#include "Rect2D.h"

namespace BadgerMath
{
	// After calling, rect's p0 will be the min point and p1 will be the max point.
	template<typename T>
	inline void trimToBounds(Rect2D<T>& rect, const Rect2D<T>& bounds)
	{
		Vector2D<T> min = rect.min();
		Vector2D<T> max = rect.max();

		min.ensureAxesNoLessThan(bounds.min());
		min.ensureAxesNoGreaterThan(bounds.max());

		max.ensureAxesNoLessThan(bounds.min());
		max.ensureAxesNoGreaterThan(bounds.max());

		rect.setP0(min);
		rect.setP1(max);
	}

	// If the reduction amount would cause the rect to be empty, it is centred around its midpoint.
	template<typename T, typename V>
	inline void shrink(Rect2D<T>& rect, const V& amount)
	{
		using Point = typename Rect2D<T>::Point;

		Point max = rect.max();
		Point min = rect.min();

		const Point mid = min + ((max - min) / static_cast<T>(2));
		const Point delta(static_cast<T>(amount), static_cast<T>(amount));

		max -= delta;
		max.ensureAxesNoLessThan(mid);

		min += delta;
		min.ensureAxesNoGreaterThan(mid);

		rect.setP0(min);
		rect.setP1(max);
	}

	// Adjusts the rect so that its top left corner is located at pos.
	// The dimensions of the rect remain the same.
	template<typename T>
	inline void translateToPosition(Rect2D<T>& rect, const typename Rect2D<T>::Point& pos)
	{
		rect = Rect2D<T>(pos, rect.width(), rect.height());
	}
}
