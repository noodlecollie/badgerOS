#include <cstddef>
#include <cstdint>
#include <cstdarg>

namespace StringLib
{
	// Safe versions of the C library functions, which will always terminate the target string.
	int snprintf_safe(char* buffer, size_t bufferSize, const char* format, ...);
	int vsnprintf_safe(char* buffer, size_t bufferSize, const char* format, va_list args);

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
	bool toFloat(const char* string, float* out);
	bool toInt(const char* string, int* out);

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
