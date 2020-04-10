#pragma once

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <CoreUtil/BgrsAssert.h>

namespace BadgerMath
{
	template<typename T>
	class Vector2D
	{
	public:
		using ValueType = T;

		inline Vector2D(const ValueType& x = 0, const ValueType& y = 0) :
			m_X(x),
			m_Y(y)
		{
		}

		inline Vector2D(const Vector2D& other)
		{
			*this = other;
		}

		template<typename VAL>
		inline Vector2D<VAL> valueCast() const
		{
			return Vector2D<VAL>(static_cast<VAL>(m_X), static_cast<VAL>(m_Y));
		}

		// Same as above, but the type is the vector class itself.
		template<typename VEC>
		inline VEC vector2DCast() const
		{
			return valueCast<typename VEC::ValueType>();
		}

		inline ValueType x() const
		{
			return m_X;
		}

		inline void setX(const ValueType& x)
		{
			m_X = x;
		}

		inline ValueType y() const
		{
			return m_Y;
		}

		inline void setY(const ValueType& y)
		{
			m_Y = y;
		}

		inline bool isNull() const
		{
			return m_X == 0 && m_Y == 0;
		}

		inline float magnitudeSquared() const
		{
			return (static_cast<float>(m_X) * static_cast<float>(m_X)) +
				   (static_cast<float>(m_Y) * static_cast<float>(m_Y));
		}

		inline float magnitude() const
		{
			return std::sqrt(magnitudeSquared());
		}

		inline void ensureAxesNoLessThan(const Vector2D& other)
		{
			m_X = std::max(m_X, other.m_X);
			m_Y = std::max(m_Y, other.m_Y);
		}

		inline void ensureAxesNoGreaterThan(const Vector2D& other)
		{
			m_X = std::min(m_X, other.m_X);
			m_Y = std::min(m_Y, other.m_Y);
		}

		inline ValueType& operator [](uint8_t index)
		{
			switch ( index )
			{
				case 0:
				{
					return m_X;
				}

				case 1:
				{
					return m_Y;
				}

				default:
				{
					BGRS_ASSERTD(false, "Index out of range.");

					static ValueType dummy = 0;
					return dummy;
				}
			}
		}

		inline const ValueType& operator [](uint8_t index) const
		{
			switch ( index )
			{
				case 0:
				{
					return m_X;
				}

				case 1:
				{
					return m_Y;
				}

				default:
				{
					BGRS_ASSERTD(false, "Index out of range.");

					static ValueType dummy = 0;
					return dummy;
				}
			}
		}

		inline Vector2D& operator =(const Vector2D& other)
		{
			m_X = other.m_X;
			m_Y = other.m_Y;
			return *this;
		}

		inline bool operator ==(const Vector2D& other) const
		{
			return m_X == other.m_X && m_Y == other.m_Y;
		}

		inline bool operator !=(const Vector2D& other) const
		{
			return !(*this == other);
		}

	private:
		ValueType m_X = 0;
		ValueType m_Y = 0;
	};

	template<typename T>
	inline Vector2D<T> operator +(const Vector2D<T>& a, const Vector2D<T>& b)
	{
		return Vector2D<T>(a.x() + b.x(), a.y() + b.y());
	}

	template<typename T>
	inline Vector2D<T>& operator +=(Vector2D<T>& a, const Vector2D<T>& b)
	{
		a[0] += b[0];
		a[1] += b[1];
		return a;
	}

	template<typename T>
	inline Vector2D<T> operator -(const Vector2D<T>& a, const Vector2D<T>& b)
	{
		return Vector2D<T>(a.x() - b.x(), a.y() - b.y());
	}

	template<typename T>
	inline Vector2D<T>& operator -=(Vector2D<T>& a, const Vector2D<T>& b)
	{
		a[0] -= b[0];
		a[1] -= b[1];
		return a;
	}

	template<typename T>
	inline Vector2D<T> operator *(const Vector2D<T>& a, const T& factor)
	{
		return Vector2D<T>(a.x() * factor, a.y() * factor);
	}

	template<typename T>
	inline Vector2D<T>& operator *=(Vector2D<T>& a, const T& factor)
	{
		a[0] *= factor;
		a[1] *= factor;
		return a;
	}

	template<typename T>
	inline Vector2D<T> operator /(const Vector2D<T>& a, const T& divisor)
	{
		BGRS_ASSERT(divisor != 0, "Division of Vector2D by 0");

		return divisor != 0 ? Vector2D<T>(a.x() / divisor, a.y() / divisor) : Vector2D<T>();
	}

	template<typename T>
	inline Vector2D<T>& operator /=(Vector2D<T>& a, const T& divisor)
	{
		BGRS_ASSERT(divisor != 0, "Division of Vector2D by 0");

		if ( divisor != 0 )
		{
			a[0] /= divisor;
			a[1] /= divisor;
		}

		return a;
	}
}
