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
		static constexpr size_t MAX_PALETTE_LENGTH = 256;

		inline BitmapSurface(uint16_t width, uint16_t height, void* data, uint8_t bitDepth = 8) :
			m_Dimensions(width, height),
			m_BitDepth(bitDepth),
			m_Pixels(data)
		{
			if ( m_BitDepth > MAX_BIT_DEPTH )
			{
				BGRS_ASSERTD(false, "Maximum bit depth exceeded.");
				m_BitDepth = MAX_BIT_DEPTH;
			}

			BGRS_ASSERTD(m_Dimensions.x() > 0, "X dimension was zero.");
			BGRS_ASSERTD(m_Dimensions.y() > 0, "Y dimension was zero.");
			BGRS_ASSERTD(m_BitDepth > 0, "Bit depth was zero.");
		}

		inline bool isValid() const
		{
			return !m_Dimensions.isNull() && m_BitDepth > 0 && m_Pixels;
		}

		inline bool hasPalette() const
		{
			return m_Palette != nullptr;
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

		inline uint16_t paletteLength() const
		{
			return hasPalette() ? static_cast<size_t>(m_PaletteLengthMinusOne) + 1 : 0;
		}

		inline uint16_t paletteDataSize() const
		{
			return hasPalette() ? (m_PaletteLengthMinusOne + 1) * paletteByteDepth() : 0;
		}

		inline uint8_t paletteBitDepth() const
		{
			return hasPalette() ? m_PaletteBitDepth : 0;
		}

		inline uint8_t paletteByteDepth() const
		{
			return hasPalette() ? bitDepthToByteDepth(m_PaletteBitDepth) : 0;
		}

		inline SurfaceVector dimensions() const
		{
			return m_Dimensions;
		}

		inline SurfaceRect bounds() const
		{
			return SurfaceRect(SurfaceVector(0, 0), width(), height());
		}

		inline size_t pixelDataSize() const
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

		// The palette is expected to be valid for the lifetime of this bitmap surface.
		inline void setPalette(uint8_t* palette, size_t length, uint8_t bitDepth)
		{
			if ( length > MAX_PALETTE_LENGTH )
			{
				BGRS_ASSERTD(false, "Maximum palette length exceeded.");
				length = MAX_PALETTE_LENGTH;
			}

			if ( bitDepth > MAX_BIT_DEPTH )
			{
				BGRS_ASSERTD(false, "Maximum palette bit depth exceeded.");
				bitDepth = MAX_BIT_DEPTH;
			}

			BGRS_ASSERTD(palette, "Palette data was null.");
			BGRS_ASSERTD(bitDepth > 0, "Palette bit depth was zero.");

			// Ensure that we only set up a palette if all the parameters are valid.
			if ( palette && length > 0 && bitDepth > 0 )
			{
				m_Palette = palette;
				m_PaletteLengthMinusOne = static_cast<uint8_t>(length - 1);
				m_PaletteBitDepth = bitDepth;
			}
			else
			{
				m_Palette = nullptr;
				m_PaletteLengthMinusOne = 0;
				m_PaletteBitDepth = 0;
			}
		}

		template<typename T>
		inline T* pixelData(uint16_t x = 0, uint16_t y = 0)
		{
			return const_cast<T*>(const_cast<const BitmapSurface*>(this)->pixelData<T>(x, y));
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
			return const_cast<void*>(const_cast<const BitmapSurface*>(this)->rawPixelData(x, y));
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

		template<typename T>
		inline T* paletteData(uint8_t index = 0)
		{
			return const_cast<T*>(const_cast<const BitmapSurface*>(this)->paletteData<T>(index));
		}

		template<typename T>
		inline const T* paletteData(uint8_t index = 0) const
		{
			if ( !hasPalette() )
			{
				BGRS_ASSERTD(false, "Bitmap does not have a palette.");
				return nullptr;
			}

			if ( sizeof(T) != paletteByteDepth() )
			{
				BGRS_ASSERTD(false, "Size of type did not match palette depth.");
				return nullptr;
			}

			return static_cast<const T*>(m_Palette) + index;
		}

		inline void* rawPaletteData(uint8_t index = 0)
		{
			return const_cast<void*>(const_cast<const BitmapSurface*>(this)->rawPaletteData(index));
		}

		inline const void* rawPaletteData(uint8_t index = 0) const
		{
			if ( !hasPalette() )
			{
				BGRS_ASSERTD(false, "Bitmap does not have a palette.");
				return nullptr;
			}

			if ( index > m_PaletteLengthMinusOne )
			{
				BGRS_ASSERTD(false, "Palette index was out of range.");
				return nullptr;
			}

			return m_Palette + (index * bitDepthToByteDepth(m_PaletteBitDepth));
		}

		// This function writes directly to the pixel data and ignores the palette.
		inline void fill(uint32_t colour)
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return;
			}

			const uint8_t bDepth = byteDepth();
			const size_t size = pixelDataSize();

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
		// This function writes directly to the pixel data and ignores the palette.
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

		// Writes the given row of data at the given position in the bitmap.
		// If the row of data would overflow the bounds of the bitmap, nothing is
		// written and false is returned.
		// It is assumed that the byte depth of the incoming data matches that of the bitmap.
		// The incoming data length is truncated to be a multiple of the byte depth.
		// This function writes directly to the pixel data and ignores the palette.
		inline bool blitHLine(const SurfaceVector& pos, const uint8_t* data, size_t dataSize)
		{
			if ( !data )
			{
				return false;
			}

			const uint8_t bDepth = byteDepth();
			const size_t numPixelsOfData = dataSize / bDepth;

			if ( numPixelsOfData < 1 )
			{
				// Nothing to draw.
				return true;
			}

			if ( pos.x() + numPixelsOfData > width() )
			{
				return false;
			}

			uint8_t* const dest = static_cast<uint8_t*>(rawPixelData(pos.x(), pos.y()));
			memcpy(dest, data, numPixelsOfData * bDepth);
			return true;
		}

		inline void clearPalette()
		{
			if ( hasPalette() )
			{
				memset(m_Palette, 0, paletteDataSize());
			}
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
		uint8_t* m_Palette = nullptr;
		uint8_t m_PaletteLengthMinusOne = 0;
		uint8_t m_PaletteBitDepth = 0;
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
			static_assert(BIT_DEPTH <= BitmapSurface::MAX_BIT_DEPTH, "Bit depth exceeded maximum depth.");

			static_assert(WIDTH > 0, "Width was zero.");
			static_assert(HEIGHT > 0, "Height was zero.");
			static_assert(BIT_DEPTH > 0, "Bit depth was zero.");
		}

	private:
		uint8_t m_StaticData[WIDTH * HEIGHT * bitDepthToByteDepth(BIT_DEPTH)];
	};

	template<uint16_t W, uint16_t H, size_t PL, uint8_t PD>
	class StaticPaletteBitmapSurface : public StaticBitmapSurface<W, H, 8>
	{
	public:
		static constexpr size_t PALETTE_LENGTH = PL;
		static constexpr uint8_t PALETTE_BIT_DEPTH = PD;

		inline StaticPaletteBitmapSurface() :
			StaticBitmapSurface<W, H, 8>()
		{
			static_assert(PALETTE_LENGTH <= BitmapSurface::MAX_PALETTE_LENGTH, "Palette size exceeded maximum size.");
			static_assert(PALETTE_BIT_DEPTH <= BitmapSurface::MAX_BIT_DEPTH, "Palette bit depth exceeded maximum depth.");

			static_assert(PALETTE_LENGTH > 0, "Palette length was zero.");
			static_assert(PALETTE_BIT_DEPTH > 0, "Palette bit depth was zero.");

			setPalette(m_Palette, PALETTE_LENGTH, PALETTE_BIT_DEPTH);
		}

	private:
		uint8_t m_Palette[PALETTE_LENGTH * bitDepthToByteDepth(PALETTE_BIT_DEPTH)];
	};

	template<uint16_t W, uint16_t H>
	class StaticBitmapSurface16 : public StaticBitmapSurface<W, H, 16>
	{
	};
}
