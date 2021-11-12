#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdarg>

namespace StringLib
{
	// Safe versions of the C library functions, which will always terminate the target string.
	int snprintf_safe(char* buffer, size_t bufferSize, const char* format, ...);
	int vsnprintf_safe(char* buffer, size_t bufferSize, const char* format, va_list args);
	char* strcpy_safe(char* buffer, size_t bufferSize, const char* source);
	char* strncpy_safe(char* buffer, size_t bufferSize, const char* source, size_t maxSourceChars);

	void condenseSpaces(char* str);
	bool equal(const char* str1, const char* str2);
	bool equalCaseInsensitive(const char* str1, const char* str2);
	bool beginEqual(const char* str1, const char* str2, const size_t length);
	bool hasPrefix(const char* str, const char* prefix);

	// Returns whether the entire binary input was encoded to hex.
	// groupSize is the number of input bytes to read before a space is printed to the output.
	// Each byte is converted to two hex characters. A groupSize of 0 means no space delimination occurs in the output.
	// The buffer is always filled up with as many characters as possible, even if false is returned.
	bool binaryToHex(const void* input, const size_t inputLength, char* output, const size_t outputLength, const uint8_t groupSize);

	// The standard C functions return 0 if the string is not numerical.
	// These functions actually return success or failure, to be less infuriating.
	bool toFloat(const char* string, float& out);
	bool toInt(const char* string, int32_t& out);

	// Returns a pointer to the first instance of the given delimiter.
	// If the delimiter is not found, returns a pointer to the string terminator.
	// This assumes that the string is ASCII; UTF-8 is not yet supported.
	const char* firstDelimiter(const char* string, char delimiter);

	inline size_t bytesForUTF8Char(const char* str)
	{
		if ( !str || !(*str) )
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

	// Same as above, but checks for intervening nulls in case the string is malformed.
	inline size_t bytesForUTF8CharSafe(const char* str)
	{
		if ( !str || !(*str) )
		{
			return 0;
		}

		size_t validChars = 0;

		for ( const char* const end = str + bytesForUTF8Char(str); str < end && (*str); ++str )
		{
			++validChars;
		}

		return validChars;
	}

	inline const char* nextCharUTF8(const char* str)
	{
		if ( !str )
		{
			return nullptr;
		}

		return str + bytesForUTF8CharSafe(str);
	}

	inline size_t charCodePointUTF8(const char* str)
	{
		switch ( bytesForUTF8Char(str) )
		{
			case 4:
			{
				if ( !str[1] || !str[2] || !str[3] )
				{
					// Malformed.
					return 0;
				}

				// Bits [2:0] in first byte, bits [5:0] in second, third and fourth bytes.
				return
					((static_cast<size_t>(str[0]) & 0b00000111) << 18) |
					((static_cast<size_t>(str[1]) & 0b00111111) << 12) |
					((static_cast<size_t>(str[2]) & 0b00111111) << 6) |
					(static_cast<size_t>(str[3]) & 0b00111111);
			}

			case 3:
			{
				if ( !str[1] || !str[2] )
				{
					// Malformed.
					return 0;
				}

				// Bits [3:0] in first byte, bits [5:0] in second and third bytes.
				return
					((static_cast<size_t>(str[0]) & 0b00001111) << 12) |
					((static_cast<size_t>(str[1]) & 0b00111111) << 6) |
					(static_cast<size_t>(str[2]) & 0b00111111);
			}

			case 2:
			{
				if ( !str[1] )
				{
					// Malformed.
					return 0;
				}

				// Bits [4:0] in first byte, bits [5:0] in second byte.
				return
					((static_cast<size_t>(str[0]) & 0b00011111) << 6) |
					(static_cast<size_t>(str[1]) & 0b00111111);
			}

			case 1:
			{
				return static_cast<size_t>(*str);
				break;
			}

			default:
			{
				// Invalid.
				return 0;
			}
		}
	}
}
