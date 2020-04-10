#pragma once

#include <cstddef>
#include <cstdint>

namespace Resources
{
	struct StaticImageMetadata
	{
		size_t width;
		size_t height;
		uint8_t bitDepth;
		bool isRowMajor;
		const void* data;
	};
}
