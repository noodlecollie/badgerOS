#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <BadgerMath/Vector2D.h>
#include <BadgerMath/Rect2D.h>
#include <BadgerMath/Rect2DOperations.h>
#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/DataUtil.h>
#include "Defs.h"

namespace BadgerGL
{
	// Class used to encapsulate a surface of pixels of fixed dimensions and depth.
	// The depth is in bits, and pixels are assumed not to be bit-packed; for example,
	// a bit depth of 10 bits would use two bytes per pixel.
	// Data is assumed to be in row-major format, and the data pointer that is passed
	// in is assumed to exist for the lifetime of this surface.
	class BitmapSurface
	{
	public:
		using SurfaceVector = BadgerMath::Vector2D<uint16_t>;
		using SurfaceRect = BadgerMath::Rect2D<uint16_t>;

		static constexpr uint8_t MAX_BIT_DEPTH = 32;

		inline BitmapSurface(uint16_t width, uint16_t height, void* data, uint8_t bitDepth = 8) :
			m_Dimensions(width, height),
			m_BitDepth(bitDepth),
			m_Pixels(data)
		{
			if ( bitDepth > MAX_BIT_DEPTH )
			{
				BGRS_ASSERTD(false, "Maximum bit depth exceeded.");
				bitDepth = MAX_BIT_DEPTH;
			}
		}

		inline bool isValid() const
		{
			return !m_Dimensions.isNull() && m_BitDepth > 0 && m_Pixels;
		}

		inline uint16_t width() const
		{
			return m_Dimensions.x();
		}

		inline uint16_t height() const
		{
			return m_Dimensions.y();
		}

		inline uint8_t bitDepth() const
		{
			return m_BitDepth;
		}

		inline uint8_t byteDepth() const
		{
			return bitDepthToByteDepth(m_BitDepth);
		}

		inline SurfaceVector dimensions() const
		{
			return m_Dimensions;
		}

		inline SurfaceRect bounds() const
		{
			return SurfaceRect(SurfaceVector(0, 0), width(), height());
		}

		inline size_t dataSize() const
		{
			return m_Dimensions.x() * m_Dimensions.y() * byteDepth();
		}

		// Returns the number of bytes on the specified dimension: width, height, or depth.
		inline uint16_t dimension(uint8_t axis) const
		{
			switch ( axis )
			{
				case 0:
				{
					return m_Dimensions.x();
				}

				case 1:
				{
					return m_Dimensions.y();
				}

				case 2:
				{
					return byteDepth();
				}

				default:
				{
					BGRS_ASSERTD(false, "Axis was not valid.");
					return 0;
				}
			}
		}

		template<typename T>
		inline T* pixelData(uint16_t x = 0, uint16_t y = 0)
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return nullptr;
			}

			if ( sizeof(T) != byteDepth() )
			{
				BGRS_ASSERTD(false, "Size of pixel type did not match pixel depth.");
				return nullptr;
			}

			return static_cast<T*>(m_Pixels) + dataOffset(x, y);
		}

		template<typename T>
		inline const T* pixelData(uint16_t x = 0, uint16_t y = 0) const
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return nullptr;
			}

			if ( sizeof(T) != byteDepth() )
			{
				BGRS_ASSERTD(false, "Size of pixel type did not match pixel depth.");
				return nullptr;
			}

			return static_cast<const T*>(m_Pixels) + dataOffset(x, y);
		}

		inline void* rawPixelData(uint16_t x = 0, uint16_t y = 0)
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return nullptr;
			}

			return static_cast<void*>(static_cast<uint8_t*>(m_Pixels) + byteDataOffset(x, y));
		}

		inline const void* rawPixelData(uint16_t x = 0, uint16_t y = 0) const
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return nullptr;
			}

			return static_cast<void*>(static_cast<uint8_t*>(m_Pixels) + byteDataOffset(x, y));
		}

		inline void fill(uint32_t colour)
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return;
			}

			const uint8_t bDepth = byteDepth();
			const size_t size = dataSize();

			if ( bDepth == 1 )
			{
				// Just flat memset the lowest byte in the colour.
				memset(m_Pixels, colour & 0x000000FF, size);
			}
			else if ( bDepth <= (MAX_BIT_DEPTH / 8) )
			{
				uint8_t* cursor = static_cast<uint8_t*>(m_Pixels);
				uint8_t* const end = cursor + size;

				while ( cursor < end )
				{
					// Write the lowest byte in the colour buffer.
					*(cursor++) = (colour & 0x000000FF);

					// Rotate the bytes down.
					colour = CoreUtil::rotateBytesDown(colour, bDepth);
				}
			}
		}

		// It is the caller's responsibility to ensure that the passed rectangle fits on the bitmap.
		// If this is not the case, nothing will be drawn and false will be returned.
		inline bool fillRect(const SurfaceRect& rect, uint32_t colour)
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return false;
			}

			if ( rect.isEmpty() )
			{
				// Technically, this is drawn correctly (ie. not at all).
				return true;
			}

			const SurfaceVector rectMin = rect.min();
			const size_t rectWidth = rect.width();
			const size_t rectHeight = rect.height();

			if ( rectMin.x() + rectWidth > width() || rectMin.y() + rectHeight > height() )
			{
				return false;
			}

			const uint8_t bDepth = byteDepth();

			for ( uint32_t row = 0; row < rectHeight; ++row )
			{
				uint8_t* cursor = static_cast<uint8_t*>(rawPixelData(rect.p0().x(), rect.p0().y() + row));

				if ( bDepth == 1 )
				{
					// Just flat memset the lowest byte in the colour.
					memset(cursor, colour & 0x000000FF, rectWidth);
				}
				else
				{
					uint8_t* const end = cursor + (rectWidth * bDepth);

					while ( cursor < end )
					{
						// Write the lowest byte in the colour buffer.
						*(cursor++) = (colour & 0x000000FF);

						// Rotate the bytes down.
						colour = CoreUtil::rotateBytesDown(colour, bDepth);
					}
				}
			}

			return true;
		}

	private:
		inline uint32_t dataOffset(uint16_t x, uint16_t y) const
		{
			return (y * m_Dimensions.x()) + x;
		}

		inline uint32_t byteDataOffset(uint16_t x, uint16_t y) const
		{
			return byteDepth() * ((y * m_Dimensions.x()) + x);
		}

		SurfaceVector m_Dimensions;
		uint8_t m_BitDepth = 0;
		void* m_Pixels = nullptr;
	};

	template<uint16_t W, uint16_t H, uint8_t D = 8>
	class StaticBitmapSurface : public BitmapSurface
	{
	public:
		static constexpr uint16_t WIDTH = W;
		static constexpr uint16_t HEIGHT = H;
		static constexpr uint8_t BIT_DEPTH = D;

		inline StaticBitmapSurface() :
			BitmapSurface(WIDTH, HEIGHT, m_StaticData, BIT_DEPTH)
		{
		}

	private:
		uint8_t m_StaticData[WIDTH * HEIGHT * bitDepthToByteDepth(BIT_DEPTH)];
	};

	template<uint16_t W, uint16_t H>
	class StaticBitmapSurface16 : public StaticBitmapSurface<W, H, 16>
	{
	};
}
