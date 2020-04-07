#pragma once

#include <cstdint>

namespace BadgerGL
{
	namespace Math
	{
		static constexpr uint8_t bitDepthToByteDepth(uint8_t bitDepth)
		{
			return (bitDepth + 7) / 8;
		}
	}
}
