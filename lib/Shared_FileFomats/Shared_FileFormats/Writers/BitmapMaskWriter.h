#pragma once

#include <cstdint>
#include "FileWriter.h"
#include "../DLLAPI.h"

namespace FileFormats
{
	namespace BitmapMask
	{
		FILEFORMATSLIB_API bool write(const FileWriter& writer, uint16_t width, uint16_t height, const void* data, size_t dataLength);
	}
}
