#pragma once

#include <cstdint>
#include <algorithm>
#include "CoreUtil/BgrsAssert.h"
#include "Vector2D.h"

namespace BadgerMath
{
	// Class that encapsulates a 2D rectangle using two points.
	// p0 and p1 are not constrained to correspond to the rectangle's min and
	// max. If the min and max points are required, use:
	// - min() and max() to get the individual points.
	// - ensureMinMaxOrdered() to re-order the points within the current rect
	//   so that p0 == min() and p1 == max().
	// - asBounds() to return a copy of the rect where p0 == min() and p1 == max().
	template<typename T>
	class Rect2D
	{
	public:
		using ValueType = T;
		using Point = Vector2D<ValueType>;

		inline Rect2D()
		{
		}

		inline Rect2D(const Point& p0, const Point& p1) :
			m_P0(p0),
			m_P1(p1)
		{
		}

		inline Rect2D(const Point& p0, size_t width, size_t height) :
			m_P0(p0),
			m_P1(p0.x() + width, p0.y() + height)
		{
		}

		inline Rect2D(const ValueType& p0x, const ValueType& p0y, const ValueType& p1x, const ValueType& p1y) :
			m_P0(p0x, p0y),
			m_P1(p1x, p1y)
		{
		}

		inline Rect2D(const Rect2D& other)
		{
			*this = other;
		}

		template<typename T2>
		inline Rect2D<T2> valueCast() const
		{
			return Rect2D<T2>(m_P0.valueCast<T2>(), m_P1.valueCast<T2>());
		}

		// Same as above, but the type is the rect class itself.
		template<typename RECT>
		inline RECT rect2DCast() const
		{
			return valueCast<typename RECT::ValueType>();
		}

		inline Point p0() const
		{
			return m_P0;
		}

		inline void setP0(const Point& p)
		{
			m_P0 = p;
		}

		inline Point p1() const
		{
			return m_P1;
		}

		inline void setP1(const Point& p)
		{
			m_P1 = p;
		}

		inline Point min() const
		{
			return Point(std::min(m_P0.x(), m_P1.x()), std::min(m_P0.y(), m_P1.y()));
		}

		inline Point max() const
		{
			return Point(std::max(m_P0.x(), m_P1.x()), std::max(m_P0.y(), m_P1.y()));
		}

		// Swaps values if required, so that p0 represents the minimum point of the rect,
		// and p1 represents tha maximum point.
		inline void ensureMinMaxOrdered()
		{
			if ( m_P0[0] > m_P1[0] )
			{
				std::swap(m_P0[0], m_P1[0]);
			}

			if ( m_P0[1] > m_P1[1] )
			{
				std::swap(m_P0[1], m_P1[1]);
			}
		}

		inline Rect2D asBounds() const
		{
			return Rect2D(min(), max());
		}

		inline size_t width() const
		{
			return (m_P1.x() > m_P0.x())
				? (m_P1.x() - m_P0.x())
				: (m_P0.x() - m_P1.x());
		}

		inline size_t height() const
		{
			return (m_P1.y() > m_P0.y())
				? (m_P1.y() - m_P0.y())
				: (m_P0.y() - m_P1.y());
		}

		inline bool isNull() const
		{
			return width() == 0 && height() == 0;
		}

		inline bool isEmpty() const
		{
			return width() == 0 || height() == 0;
		}

		inline size_t area() const
		{
			return width() * height();
		}

		inline Rect2D& operator =(const Rect2D& other)
		{
			m_P0 = other.m_P0;
			m_P1 = other.m_P1;

			return *this;
		}

	private:
		Point m_P0;
		Point m_P1;
	};
}
