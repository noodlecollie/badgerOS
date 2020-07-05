#pragma once

namespace CoreUtil
{
	inline const char* nextCharUTF8(const char* str)
	{
		if ( !str )
		{
			return nullptr;
		}

		// 4-byte sequence starts with binary 11110.
		if ( ((*str) & 0b11111000) == 0b11110000 )
		{
			return str + 4;
		}

		// 3-byte sequence starts with binary 1110.
		if ( ((*str) & 0b11110000) == 0b11100000 )
		{
			return str + 3;
		}

		// 2-byte sequence starts with binary 110.
		if ( ((*str) & 0b11100000) == 0b11000000 )
		{
			return str + 2;
		}

		return str + 1;
	}
}
