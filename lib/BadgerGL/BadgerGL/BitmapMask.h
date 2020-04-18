#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <BadgerMath/Vector2D.h>
#include <BadgerMath/Rect2D.h>
#include "Defs.h"

namespace BadgerGL
{
	// Class representinga binary (1 or 0) bitmap which is read-only.
	// Each bit in the mask is packed into the data bytes, in row-major order.
	// If a row dimensions is not a multiple of 8, the rest of the bits in the
	// byte are treated as undefined padding.
	class BitmapMask
	{
	public:
		using SurfaceVector = BadgerMath::Vector2D<uint16_t>;
		using SurfaceRect = BadgerMath::Rect2D<uint16_t>;

		// Constexpr constructors assume that all inputs are valid.
		constexpr BitmapMask(uint16_t inWidth, uint16_t inHeight, const uint8_t* inData) :
			m_Dimensions(inWidth, inHeight),
			m_Pixels(inData)
		{
		}

		inline bool isValid() const
		{
			return m_Dimensions.x() > 0 && m_Dimensions.y() > 0 && m_Pixels;
		}

		inline uint16_t width() const
		{
			return m_Dimensions.x();
		}

		inline uint16_t height() const
		{
			return m_Dimensions.y();
		}

		inline SurfaceVector dimensions() const
		{
			return m_Dimensions;
		}

		inline SurfaceRect bounds() const
		{
			return SurfaceRect(SurfaceVector(0, 0), width(), height());
		}

		inline size_t rowWidthInBytes() const
		{
			return bitDepthToByteDepth(m_Dimensions.x());
		}

		inline size_t pixelDataSize() const
		{
			return maskedDataSizeForDimensions(m_Dimensions.x(), m_Dimensions.y());
		}

		inline const uint8_t* constPixelData(uint16_t x = 0, uint16_t y = 0) const
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return nullptr;
			}

			if ( x >= m_Dimensions.x() || y >= m_Dimensions.y() )
			{
				BGRS_ASSERTD(false, "Pixel co-ordinates were out of range.");
				return nullptr;
			}

			return m_Pixels + dataOffset(x, y);
		}

		inline uint8_t maskValue(uint16_t x, uint16_t y) const
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return 0;
			}

			if ( x >= m_Dimensions.x() || y >= m_Dimensions.y() )
			{
				BGRS_ASSERTD(false, "Pixel co-ordinates were out of range.");
				return 0;
			}

			return (m_Pixels[dataOffset(x, y)] >> (x % 8)) & 0x1;
		}

	private:
		inline uint32_t dataOffset(uint16_t x, uint16_t y) const
		{
			return (y * rowWidthInBytes()) + (x / 8);
		}

		SurfaceVector m_Dimensions;
		const uint8_t* m_Pixels = nullptr;
	};
}
