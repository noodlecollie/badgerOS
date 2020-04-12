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
	// Data is assumed to be in row-major format, and the data pointers passed in for
	// both the bitmap and the palette, if applicable, are assumed to exist for the
	// lifetime of this surface.
	// The data passed into this class is assumed not to be modifiable.
	class ConstBitmapSurface
	{
	public:
		using SurfaceVector = BadgerMath::Vector2D<uint16_t>;
		using SurfaceRect = BadgerMath::Rect2D<uint16_t>;

		static constexpr uint8_t MAX_BIT_DEPTH = 32;
		static constexpr size_t MAX_PALETTE_LENGTH = 256;
		static constexpr uint8_t MAX_BIT_DEPTH_FOR_PALETTE = 8;

		struct ConstBitmapInitialiser
		{
			inline ConstBitmapInitialiser(uint16_t inWidth, uint16_t inHeight, uint8_t inBitDepth, const void* inData) :
				width(inWidth),
				height(inHeight),
				bitDepth(inBitDepth),
				data(inData)
			{
			}

			inline bool isValid() const
			{
				return
					width > 0 &&
					height > 0 &&
					bitDepth > 0 &&
					bitDepth <= ConstBitmapSurface::MAX_BIT_DEPTH &&
					data;
			}

			uint16_t width = 0;
			uint16_t height = 0;
			uint8_t bitDepth = 0;
			const void* data = nullptr;
		};

		struct ConstPaletteInitialiser
		{
			inline ConstPaletteInitialiser()
			{
			}

			inline ConstPaletteInitialiser(size_t inLength, uint8_t inBitDepth, const void* inData) :
				length(inLength),
				bitDepth(inBitDepth),
				data(inData)
			{
			}

			inline bool isValid() const
			{
				return
					length > 0 &&
					length <= ConstBitmapSurface::MAX_PALETTE_LENGTH &&
					bitDepth > 0 &&
					bitDepth <= ConstBitmapSurface::MAX_BIT_DEPTH &&
					data;
			}

			size_t length = 0;
			uint8_t bitDepth = 0;
			const void* data = 0;
		};

		inline ConstBitmapSurface(const ConstBitmapInitialiser& bitmap, const ConstPaletteInitialiser palette = ConstPaletteInitialiser())
		{
			if ( !bitmap.isValid() )
			{
				BGRS_ASSERTD(false, "Provided bitmap data was not valid.");
				return;
			}

			if ( palette.isValid() && bitmap.bitDepth > MAX_BIT_DEPTH_FOR_PALETTE )
			{
				BGRS_ASSERTD(false, "Maximum bit depth was exceeded for a palette bitmap.");
				return;
			}

			m_Dimensions = SurfaceVector(bitmap.width, bitmap.height);
			m_BitDepth = bitmap.bitDepth;
			m_Pixels = bitmap.data;

			if ( palette.isValid() )
			{
				m_Palette = palette.data;
				m_PaletteBitDepth = palette.bitDepth;
				m_PaletteLengthMinusOne = static_cast<uint8_t>(palette.length - 1);
			}
		}

		inline bool isValid() const
		{
			return !m_Dimensions.isNull() && m_BitDepth > 0 && m_Pixels;
		}

		inline bool hasPalette() const
		{
			return m_Palette != nullptr;
		}

		// TODO: Swap out bit depth for actual pixel format description of some sort,
		// so that we have information on channels.
		inline bool pixelFormat() const
		{
			return hasPalette() ? paletteBitDepth() : bitDepth();
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

		template<typename T>
		inline const T* constPixelData(uint16_t x = 0, uint16_t y = 0) const
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

		inline const void* constRawPixelData(uint16_t x = 0, uint16_t y = 0) const
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Bitmap was not valid.");
				return nullptr;
			}

			return static_cast<const void*>(static_cast<const uint8_t*>(m_Pixels) + byteDataOffset(x, y));
		}

		template<typename T>
		inline const T* constPaletteData(uint8_t index = 0) const
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

			if ( sizeof(T) != paletteByteDepth() )
			{
				BGRS_ASSERTD(false, "Size of type did not match palette depth.");
				return nullptr;
			}

			return static_cast<const T*>(m_Palette) + index;
		}

		inline const void* constRawPaletteData(uint8_t index = 0) const
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

			return static_cast<const uint8_t*>(m_Palette) + (index * bitDepthToByteDepth(m_PaletteBitDepth));
		}

	protected:
		inline uint32_t dataOffset(uint16_t x, uint16_t y) const
		{
			return (y * m_Dimensions.x()) + x;
		}

		inline uint32_t byteDataOffset(uint16_t x, uint16_t y) const
		{
			return byteDepth() * ((y * m_Dimensions.x()) + x);
		}

	private:
		SurfaceVector m_Dimensions;
		uint8_t m_BitDepth = 0;
		const void* m_Pixels = nullptr;

		uint8_t m_PaletteLengthMinusOne = 0;
		uint8_t m_PaletteBitDepth = 0;
		const void* m_Palette = nullptr;
	};

	// This class builds upon the ConstBitmapSurface class to provide mutators.
	// It is assumed that the data passed into this class is modifiable.
	class BitmapSurface : public ConstBitmapSurface
	{
	public:
		using SurfaceVector = ConstBitmapSurface::SurfaceVector;
		using SurfaceRect = ConstBitmapSurface::SurfaceRect;

		static constexpr uint8_t MAX_BIT_DEPTH = ConstBitmapSurface::MAX_BIT_DEPTH;
		static constexpr size_t MAX_PALETTE_LENGTH = ConstBitmapSurface::MAX_PALETTE_LENGTH;
		static constexpr uint8_t MAX_BIT_DEPTH_FOR_PALETTE = ConstBitmapSurface::MAX_BIT_DEPTH_FOR_PALETTE;

		struct BitmapInitialiser
		{
			inline BitmapInitialiser(uint16_t inWidth, uint16_t inHeight, uint8_t inBitDepth, void* inData) :
				width(inWidth),
				height(inHeight),
				bitDepth(inBitDepth),
				data(inData)
			{
			}

			inline bool isValid() const
			{
				return
					width > 0 &&
					height > 0 &&
					bitDepth > 0 &&
					bitDepth <= ConstBitmapSurface::MAX_BIT_DEPTH &&
					data;
			}

			uint16_t width = 0;
			uint16_t height = 0;
			uint8_t bitDepth = 0;
			void* data = nullptr;
		};

		struct PaletteInitialiser
		{
			inline PaletteInitialiser()
			{
			}

			inline PaletteInitialiser(size_t inLength, uint8_t inBitDepth, void* inData) :
				length(inLength),
				bitDepth(inBitDepth),
				data(inData)
			{
			}

			inline bool isValid() const
			{
				return
					length > 0 &&
					length <= ConstBitmapSurface::MAX_PALETTE_LENGTH &&
					bitDepth > 0 &&
					bitDepth <= ConstBitmapSurface::MAX_BIT_DEPTH &&
					data;
			}

			size_t length = 0;
			uint8_t bitDepth = 0;
			void* data = 0;
		};

		inline BitmapSurface(const BitmapInitialiser& bitmap, const PaletteInitialiser palette = PaletteInitialiser()) :
			ConstBitmapSurface(ConstBitmapInitialiser(bitmap.width, bitmap.height, bitmap.bitDepth, bitmap.data),
							   ConstPaletteInitialiser(palette.length, palette.bitDepth, palette.data))
		{
		}

		// Any const_casts in the functions below are safe, because we know that the data we originally
		// provided to the base class was modifiable.

		template<typename T>
		inline T* pixelData(uint16_t x = 0, uint16_t y = 0)
		{
			return const_cast<T*>(constPixelData<T>(x, y));
		}

		inline void* rawPixelData(uint16_t x = 0, uint16_t y = 0)
		{
			return const_cast<void*>(constRawPixelData(x, y));
		}

		template<typename T>
		inline T* paletteData(uint8_t index = 0)
		{
			return const_cast<T*>(constPaletteData<T>(index));
		}

		inline void* rawPaletteData(uint8_t index = 0)
		{
			return const_cast<void*>(constRawPaletteData(index));
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
			uint8_t* pixels = static_cast<uint8_t*>(rawPixelData());

			if ( bDepth == 1 )
			{
				// Just flat memset the lowest byte in the colour.
				memset(pixels, colour & 0x000000FF, size);
			}
			else if ( bDepth <= (MAX_BIT_DEPTH / 8) )
			{
				uint8_t* const end = pixels + size;

				while ( pixels < end )
				{
					// Write the lowest byte in the colour buffer.
					*(pixels++) = (colour & 0x000000FF);

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
				memset(rawPaletteData(), 0, paletteDataSize());
			}
		}
	};

	template<uint16_t W, uint16_t H, uint8_t D = 8>
	class StaticBitmapSurface : public BitmapSurface
	{
	public:
		using BitmapInitialiser = BitmapSurface::BitmapInitialiser;
		using PaletteInitialiser = BitmapSurface::PaletteInitialiser;

		static constexpr uint16_t WIDTH = W;
		static constexpr uint16_t HEIGHT = H;
		static constexpr uint8_t BIT_DEPTH = D;

		inline StaticBitmapSurface() :
			StaticBitmapSurface(BitmapInitialiser(WIDTH, HEIGHT, BIT_DEPTH, m_StaticData), PaletteInitialiser())
		{
		}

	protected:
		inline StaticBitmapSurface(const PaletteInitialiser& palette) :
			StaticBitmapSurface(BitmapInitialiser(WIDTH, HEIGHT, BIT_DEPTH, m_StaticData), palette)
		{
		}

	private:
		inline StaticBitmapSurface(const BitmapInitialiser& bitmap, const PaletteInitialiser& palette) :
			BitmapSurface(bitmap, palette)
		{
			static_assert(BIT_DEPTH <= BitmapSurface::MAX_BIT_DEPTH, "Bit depth exceeded maximum depth.");

			static_assert(WIDTH > 0, "Width was zero.");
			static_assert(HEIGHT > 0, "Height was zero.");
			static_assert(BIT_DEPTH > 0, "Bit depth was zero.");
		}

		uint8_t m_StaticData[WIDTH * HEIGHT * bitDepthToByteDepth(BIT_DEPTH)];
	};

	template<uint16_t W, uint16_t H, size_t PL, uint8_t PD>
	class StaticPaletteBitmapSurface : public StaticBitmapSurface<W, H, 8>
	{
	public:
		using BaseClass = StaticBitmapSurface<W, H, 8>;
		using BitmapInitialiser = typename BaseClass::BitmapInitialiser;
		using PaletteInitialiser = typename BaseClass::PaletteInitialiser;

		static constexpr uint16_t WIDTH = BaseClass::WIDTH;
		static constexpr uint16_t HEIGHT = BaseClass::HEIGHT;
		static constexpr uint8_t BIT_DEPTH = BaseClass::BIT_DEPTH;
		static constexpr size_t PALETTE_LENGTH = PL;
		static constexpr uint8_t PALETTE_BIT_DEPTH = PD;

		inline StaticPaletteBitmapSurface() :
			BaseClass(PaletteInitialiser(PALETTE_LENGTH, PALETTE_BIT_DEPTH, m_Palette))
		{
			static_assert(PALETTE_LENGTH <= BitmapSurface::MAX_PALETTE_LENGTH, "Palette size exceeded maximum size.");
			static_assert(PALETTE_BIT_DEPTH <= BitmapSurface::MAX_BIT_DEPTH, "Palette bit depth exceeded maximum depth.");

			static_assert(PALETTE_LENGTH > 0, "Palette length was zero.");
			static_assert(PALETTE_BIT_DEPTH > 0, "Palette bit depth was zero.");
		}

	private:
		uint8_t m_Palette[PALETTE_LENGTH * bitDepthToByteDepth(PALETTE_BIT_DEPTH)];
	};

	template<uint16_t W, uint16_t H>
	class StaticBitmapSurface16 : public StaticBitmapSurface<W, H, 16>
	{
	};
}