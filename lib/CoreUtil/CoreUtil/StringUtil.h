#pragma once

#include <cstddef>

namespace CoreUtil
{
	inline size_t bytesForUTF8Char(const char* str)
	{
		if ( !str )
		{
			return 0;
		}

		// 4-byte sequence starts with binary 11110.
		if ( ((*str) & 0b11111000) == 0b11110000 )
		{
			return 4;
		}

		// 3-byte sequence starts with binary 1110.
		if ( ((*str) & 0b11110000) == 0b11100000 )
		{
			return 3;
		}

		// 2-byte sequence starts with binary 110.
		if ( ((*str) & 0b11100000) == 0b11000000 )
		{
			return 2;
		}

		return 1;
	}

	inline const char* nextCharUTF8(const char* str)
	{
		if ( !str )
		{
			return nullptr;
		}

		// Double-check that there are no nulls in-between.
		// If there are, we could end up running off the
		// end of the string if it's malformed UTF-8.
		const char* const end = str + bytesForUTF8Char(str);

		while ( str < end && (*str) )
		{
			++str;
		}

		return str;
	}
}
