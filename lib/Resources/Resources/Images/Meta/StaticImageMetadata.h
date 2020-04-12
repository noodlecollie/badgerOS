#pragma once

#include <cstddef>
#include <cstdint>
#include <BadgerGL/PixelFormat.h>

namespace Resources
{
	struct StaticImageMetadata
	{
		size_t width;
		size_t height;
		const BadgerGL::PixelFormat& pixelFormat;
		bool isRowMajor;
		const void* data;
	};
}
