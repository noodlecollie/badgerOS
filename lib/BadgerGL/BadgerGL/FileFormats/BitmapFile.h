#pragma once

#include <cstddef>
#include <cstdint>
#include "../PixelFormat.h"

namespace BadgerGL
{
#pragma pack(push, 1)
	struct BitmapFileHeader
	{
		static constexpr uint32_t IDENTIFIER = ('B' << 24) | ('M' << 16) | ('P' << 8) | 'F';

		uint32_t identifier;
		uint16_t width;
		uint16_t height;
		uint8_t pixelFormatId;
		uint16_t paletteLengthInPixels;
		uint8_t palettePixelFormatId;
	};
#pragma pack(pop)

	namespace BitmapFile
	{
		// Pixel data is immediately after the header.
		static inline uint32_t pixelDataOffset(const BitmapFileHeader& header)
		{
			return sizeof(BitmapFileHeader);
		}

		// Palette data, if applicable, is after the pixel data.
		static inline uint32_t paletteDataOffset(const BitmapFileHeader& header)
		{
			if ( header.pixelFormatId >= PixelFormat__Count || header.paletteLengthInPixels < 1 )
			{
				return 0;
			}

			const PixelFormat* const format = getPixelFormat(static_cast<PixelFormatId>(header.pixelFormatId));
			return format ? sizeof(BitmapFileHeader) + (header.width * header.height * format->totalByteDepth()) : 0;
		}
	}
}
