#pragma once

#include <cstddef>

namespace CoreUtil
{
	template<size_t SIZE, typename T>
	static inline constexpr size_t arraySize(T(&)[SIZE])
	{
		return SIZE;
	}
}
