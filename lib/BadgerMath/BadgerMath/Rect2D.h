#pragma once

#include <cstdint>
#include "CoreUtil/BgrsAssert.h"

namespace BadgerMath
{
	template<typename T>
	class Rect2D
	{
	public:
		using ValueType = T;

		inline Rect2D(ValueType x = 0, ValueType y = 0, ValueType width = 0, ValueType height = 0) :
			m_X(x),
			m_Y(y),
			m_Width(width),
			m_Height(height)
		{
		}

		inline ValueType x() const
		{
			return m_X;
		}

		inline void setX(ValueType x)
		{
			m_X = x;
		}

		inline ValueType y() const
		{
			return m_Y;
		}

		inline void setY(ValueType y)
		{
			m_Y = y;
		}

		inline ValueType width() const
		{
			return m_Width;
		}

		inline void setWidth(ValueType width)
		{
			m_Width = width;
		}

		inline ValueType height() const
		{
			return m_Height;
		}

		inline void setHeight(ValueType height)
		{
			m_Height = height;
		}

	private:
		ValueType m_X = 0;
		ValueType m_Y = 0;
		ValueType m_Width = 0;
		ValueType m_Height = 0;
	};

	using IRect2D = Rect2D<int32_t>;
}
