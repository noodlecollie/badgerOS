#pragma once

#include <cstdint>

namespace CoreUtil
{
	using TimevalMs = unsigned long;
	using LongTimestamp = uint64_t;

	static constexpr TimevalMs DURATION_INFINITE = ~0;
}
