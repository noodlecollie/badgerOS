#pragma once

#include <cstdint>
#include <cstddef>
#include <BadgerGL/Defs.h>

namespace FileFormats
{
	namespace BitmapMask
	{
#pragma pack(push, 1)
		struct Header
		{
			static constexpr uint32_t SIGNATURE = ('B' << 24) | ('M' << 16) | ('P' << 8) | 'M';

			uint32_t signature;
			uint16_t width;
			uint16_t height;
		};
#pragma pack(pop)

		static constexpr inline size_t sizeRequiredForFile(const Header& header)
		{
			return sizeof(Header) + BadgerGL::maskedDataSizeForDimensions(header.width, header.height);
		}
	}
}
