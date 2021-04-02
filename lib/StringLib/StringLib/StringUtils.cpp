#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include "StringUtils.h"

namespace StringLib
{
	static bool doesEntireStringRepresentZero(const char* string, size_t maxLength, bool pointAllowed)
	{
		bool encounteredZero = false;
		bool encounteredNonWhitespace = false;
		bool encounteredPoint = false;

		if ( !string )
		{
			return false;
		}

		for ( const char* ch = string; *ch && static_cast<size_t>(ch - string) < maxLength; ++ch )
		{
			if (isspace(*ch))
			{
				// After the number has begun, no more whitespace is allowed.
				if (encounteredNonWhitespace)
				{
					return false;
				}

				continue;
			}

			// If they appear, signs must be the very first non-whitespace character.
			// -0 or +0 still count as zero.
			if (*ch == '-' || *ch == '+')
			{
				if (encounteredNonWhitespace)
				{
					return false;
				}

				encounteredNonWhitespace = true;
				continue;
			}

			// Zeroes are always OK.
			// We allow strings like 0000.
			if (*ch == '0')
			{
				encounteredZero = true;
				encounteredNonWhitespace = true;
				continue;
			}

			// There must be at most one decimal point.
			// 0, .0, 0. and 0.0 are all OK.
			if (*ch == '.')
			{
				if (!pointAllowed || encounteredPoint)
				{
					return false;
				}

				encounteredPoint = true;
				encounteredNonWhitespace = true;
				continue;
			}

			// Any other character is disallowed.
			return false;
		}

		// We must have seen at least one zero.
		return encounteredZero;
	}

	// Apparently functions like atof() terminate number parsing at the first invalid character,
	// whereas we used to assume the entire string must comprise a number. Here, we compute the
	// bounds of the string section we actually want to check, before passing them on to
	// _DoesEntireStringRepresentZero().
	static bool doesFirstNumericalPartOfStringRepresentZero(const char* string, bool pointAllowed)
	{
		if ( !string )
		{
			return false;
		}

		// Wind on past any introductory whitespace.
		while ( isspace(*string) )
		{
			++string;
		}

		// Find the first invalid character.
		const char* delimiter = string;
		for ( ; *delimiter; ++delimiter )
		{
			const char ch = *delimiter;

			if ( !(ch >= '0' && ch <= '9') &&
				ch != '-' &&
				ch != '+' &&
				!(pointAllowed && ch == '.') )
			{
				break;
			}
		}

		return doesEntireStringRepresentZero(string, delimiter - string, pointAllowed);
	}

	static inline int ensureVsnprintfTerminated(char* buffer, size_t bufferSize, int vsnprintfResult)
	{
		if ( buffer && bufferSize > 0 )
		{
			if ( static_cast<size_t>(vsnprintfResult) >= bufferSize )
			{
				// String was not automatically terminated (boo, CLib).
				buffer[bufferSize - 1] = '\0';
			}
			else if ( vsnprintfResult < 1 )
			{
				// Just in case.
				buffer[0] = '\0';
			}
		}

		return vsnprintfResult;
	}

	int snprintf_safe(char* buffer, size_t bufferSize, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		const int result = vsnprintf(buffer, bufferSize, format, args);
		va_end(args);

		return result;
	}

	int vsnprintf_safe(char* buffer, size_t bufferSize, const char* format, va_list args)
	{
		return ensureVsnprintfTerminated(buffer, bufferSize, ::vsnprintf(buffer, bufferSize, format, args));
	}

	char* strcpy_safe(char* buffer, size_t bufferSize, const char* source)
	{
		if ( !buffer || bufferSize < 1 || !source )
		{
			return buffer;
		}

		while ( bufferSize-- > 1 && *source )
		{
			// We had more than one char left in the buffer, and there was another
			// source char to copy, so copy it.
			*(buffer++) = *(source++);
		}

		// ALWAYS ensure the buffer is terminated.
		*buffer = '\0';

		return buffer;
	}

	char* strncpy_safe(char* buffer, size_t bufferSize, const char* source, size_t maxSourceChars)
	{
		if ( !buffer || bufferSize < 1 || !source || maxSourceChars < 1 )
		{
			return buffer;
		}

		const size_t charsToCopy = std::min(bufferSize, maxSourceChars);
		strncpy(buffer, source, charsToCopy);

		if ( charsToCopy == bufferSize )
		{
			// We filled the buffer completely. Always make sure the last character is a null.
			buffer[bufferSize - 1] = '\0';
		}
		else if ( buffer[charsToCopy - 1] != '\0' )
		{
			// We didn't fill the buffer, but the last character copied in was not a null.
			// Make sure the next character on is a null.
			buffer[charsToCopy] = '\0';
		}

		return buffer;
	}

	// Converts sequences of consecutive space characters to a single space.
	void condenseSpaces(char* const str)
	{
		int r = 0; /* next character to be read */
		int w = 0; /* next character to be written */

		while (str[r])
		{
			if (isspace(str[r]) || iscntrl(str[r]))
			{
				if (w < 1 || !isspace(str[w - 1]))
				{
					str[w++] = ' ';
				}
			}
			else
			{
				str[w++] = str[r];
			}
			r++;
		}

		str[w] = '\0';
	}

	bool equal(const char* const str1, const char* const str2)
	{
		return strcmp(str1, str2) == 0;
	}

	bool equalCaseInsensitive(const char* const str1, const char* const str2)
	{
		return strcasecmp(str1, str2) == 0;
	}

	bool beginEqual(const char* const str1, const char* const str2, const size_t length)
	{
		return strncmp(str1, str2, length) == 0;
	}

	bool hasPrefix(const char* const str, const char* const prefix)
	{
		return strncmp(str, prefix, strlen(prefix)) == 0;
	}

	bool binaryToHex(const void* const input, const size_t inputLength, char* const output, const size_t outputLength, const uint8_t groupSize)
	{
		static constexpr const char HEX_CHARS[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		if ( !output || outputLength < 1 || !input )
		{
			return false;
		}

		const uint8_t* inBytes = (const uint8_t*)input;
		uint32_t inIndex = 0;
		uint32_t outIndex = 0;

		for ( ; inIndex < 2 * inputLength && outIndex < outputLength - 1; ++inIndex )
		{
			if ( groupSize > 0 &&					// If we are grouping,
				inIndex > 0 &&						// this is not the first group,
				inIndex % (2 * groupSize) == 0 )	// and it is the first byte of a group
			{
				// Prepend a space before further output.
				output[outIndex++] = ' ';
			}

			if ( outIndex >= outputLength - 1 )
			{
				// Out of space.
				// Wind the index back one, because we didn't actually get to write the data.
				--inIndex;
				break;
			}

			uint8_t inValue = inBytes[inIndex / 2];

			if ( inIndex % 2 == 0 )
			{
				inValue = (inValue & 0xF0) >> 4;
			}
			else
			{
				inValue = inValue & 0x0F;
			}

			output[outIndex++] = HEX_CHARS[inValue];
		}

		// Terminate.
		output[outIndex++] = '\0';

		// Return whether we wrote every byte.
		return inIndex == 2 * inputLength;
	}

	bool toFloat(const char* string, float& out)
	{
		if ( !string )
		{
			return false;
		}

		out = (float)atof(string);

		return out != 0.0f || doesFirstNumericalPartOfStringRepresentZero(string, true);
	}

	bool toInt(const char* string, int32_t& out)
	{
		if ( !string )
		{
			return false;
		}

		out = atoi(string);

		return out != 0 || doesFirstNumericalPartOfStringRepresentZero(string, false);
	}

	const char* firstDelimiter(const char* string, char delimiter)
	{
		if ( !string )
		{
			return nullptr;
		}

		while ( *string != delimiter && *string != '\0' )
		{
			++string;
		}

		return string;
	}
}
