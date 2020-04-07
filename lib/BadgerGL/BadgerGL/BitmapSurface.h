#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include "CoreUtil/BgrsAssert.h"
#include "Math.h"

namespace BadgerGL
{
	// Class used to encapsulate a surface of pixels of fixed dimensions and depth.
	// The depth is in bits, and pixels are assumed not to be bit-packed; for example,
	// a bit depth of 10 bits would use two bytes per pixel.
	// The data pointer that is passed in is assumed to exist for the lifetime of this
	// surface.
	class BitmapSurface
	{
	public:
		inline BitmapSurface(uint16_t width, uint16_t height, void* data, uint8_t bitDepth = 8) :
			m_Width(width),
			m_Height(height),
			m_BitDepth(bitDepth),
			m_Pixels(data)
		{
		}

		inline bool isValid() const
		{
			return m_Width > 0 && m_Height > 0 && m_BitDepth > 0 && m_Pixels;
		}

		inline uint16_t width() const
		{
			return m_Width;
		}

		inline uint16_t height() const
		{
			return m_Height;
		}

		inline uint8_t bitDepth() const
		{
			return m_BitDepth;
		}

		inline uint8_t byteDepth() const
		{
			return Math::bitDepthToByteDepth(m_BitDepth);
		}

		inline size_t dataSize() const
		{
			return m_Width * m_Height * byteDepth();
		}

		// Returns the number of bytes on the specified dimension: width, height, or depth.
		inline uint16_t dimension(uint8_t axis) const
		{
			BGRS_ASSERTD(axis < 3, "Axis was not valid.");

			switch ( axis )
			{
				case 0:
				{
					return m_Width;
				}

				case 1:
				{
					return m_Height;
				}

				case 2:
				{
					return byteDepth();
				}

				default:
				{
					return 0;
				}
			}
		}

		template<typename T>
		inline T* pixelData(uint16_t x = 0, uint16_t y = 0)
		{
			BGRS_ASSERTD(isValid(), "Bitmap was not valid.");
			BGRS_ASSERTD(sizeof(T) == byteDepth(), "Size of pixel type did not match pixel depth.");

			return static_cast<T*>(m_Pixels) + (y * m_Width) + x;
		}

		template<typename T>
		inline const T* pixelData(uint16_t x = 0, uint16_t y = 0) const
		{
			BGRS_ASSERTD(isValid(), "Bitmap was not valid.");
			BGRS_ASSERTD(sizeof(T) == byteDepth(), "Size of pixel type did not match pixel depth.");

			return static_cast<const T*>(m_Pixels) + (y * m_Width) + x;
		}

		inline void* rawPixelData(uint16_t x = 0, uint16_t y = 0)
		{
			BGRS_ASSERTD(isValid(), "Bitmap was not valid.");

			return static_cast<void*>(static_cast<uint8_t*>(m_Pixels) + (y * m_Width) + x);
		}

		inline const void* rawPixelData(uint16_t x = 0, uint16_t y = 0) const
		{
			BGRS_ASSERTD(isValid(), "Bitmap was not valid.");

			return static_cast<void*>(static_cast<uint8_t*>(m_Pixels) + (y * m_Width) + x);
		}

		inline void fill(uint32_t data)
		{
			BGRS_ASSERTD(isValid(), "Bitmap was not valid.");

			if ( !isValid() )
			{
				return;
			}

			const size_t size = dataSize();
			const uint8_t bDepth = byteDepth();

			if ( bDepth == 1 )
			{
				memset(m_Pixels, data, size);
			}
			else
			{
				uint8_t* cursor = static_cast<uint8_t*>(m_Pixels);
				uint8_t* const end = cursor + size;

				while ( cursor < end )
				{
					// Write the lowest byte in the data buffer.
					*(cursor++) = (data & 0x000000FF);

					// Rotate the bytes down.
					data = (data >> 8) | ((data & 0x000000FF) << (8 * (bDepth - 1)));
				}
			}
		}

	private:
		uint16_t m_Width = 0;
		uint16_t m_Height = 0;
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
		uint8_t m_StaticData[WIDTH * HEIGHT * Math::bitDepthToByteDepth(BIT_DEPTH)];
	};

	template<uint16_t W, uint16_t H>
	class StaticBitmapSurface16 : public StaticBitmapSurface<W, H, 16>
	{
	};
}
