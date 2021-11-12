#include <string.h>
#include "StringBuilder.h"
#include "StringUtils.h"

namespace StringLib
{
	StringBuilder::StringBuilder(char* buffer, size_t length) :
		m_Buffer(buffer),
		m_Size(length),
		m_Cursor(m_Buffer)
	{
		if ( isValid() )
		{
			*m_Cursor = '\0';
		}
	}

	void StringBuilder::updateCursor()
	{
		if ( !isValid() )
		{
			return;
		}

		size_t stringLength = ::strlen(m_Buffer);

		if ( stringLength >= m_Size )
		{
			// Oops! Someone's modified the string and overflowed the buffer!
			// Not much we can do from here other than reset the cursor to the correct size.
			stringLength = m_Size - 1;
		}

		setCursorIndexInternal(stringLength);
	}

	bool StringBuilder::strcat(const char* string)
	{
		if ( !isValid() || !string )
		{
			return false;
		}

		if ( !(*string) )
		{
			// Nop.
			return true;
		}

		const size_t originalLength = strlenInternal();

		while ( *string && m_Cursor < (m_Buffer + m_Size - 1) )
		{
			*(m_Cursor++) = *(string++);
		}

		*m_Cursor = '\0';
		return *string == '\0';
	}

	bool StringBuilder::strcpy(const char* string)
	{
		if ( !isValid() )
		{
			return false;
		}

		setCursorIndexInternal(0);

		return strcat(string);
	}

	bool StringBuilder::sprintf(const char* format, ...)
	{
		if ( !isValid() || !format )
		{
			return false;
		}

		va_list args;

		va_start(args, format);
		bool result = vsprintf(format, args);
		va_end(args);

		return result;
	}

	bool StringBuilder::vsprintf(const char* format, va_list args)
	{
		if ( !isValid() || !format )
		{
			return false;
		}

		return vFormatInternal(m_Buffer, format, args);
	}

	bool StringBuilder::appendFormat(const char* format, ...)
	{
		if ( !isValid() || !format )
		{
			return false;
		}

		va_list args;

		va_start(args, format);
		size_t result = appendVFormat(format, args);
		va_end(args);

		return result;
	}

	bool StringBuilder::appendVFormat(const char* format, va_list args)
	{
		if ( !isValid() || !format )
		{
			return false;
		}

		return vFormatInternal(m_Cursor, format, args);
	}

	bool StringBuilder::appendChar(char ch)
	{
		if ( !isValid() || writableCharsRemainingInternal() < 1 )
		{
			return false;
		}

		*(m_Cursor++) = ch;
		return true;
	}

	bool StringBuilder::appendRepeatedChar(char ch, size_t count)
	{
		if ( !isValid() )
		{
			return false;
		}

		while ( count > 0 && writableCharsRemainingInternal() > 0 )
		{
			*(m_Cursor++) = ch;
			--count;
		}

		return count == 0;
	}

	void StringBuilder::clear()
	{
		if ( !isValid() )
		{
			return;
		}

		setCursorIndexInternal(0);
	}

	bool StringBuilder::endsWith(const char* suffix) const
	{
		if ( !isValid() || !suffix )
		{
			return false;
		}

		const size_t suffixLength = ::strlen(suffix);

		if ( strlenInternal() < suffixLength )
		{
			return false;
		}

		return StringLib::equal(m_Cursor - suffixLength, suffix);
	}

	bool StringBuilder::strcatWithOverwrite(const char* string)
	{
		if ( !isValid() || !string )
		{
			return false;
		}

		const size_t stringLength = ::strlen(string);

		if ( stringLength > m_Size - 1 )
		{
			// Too long - erase everything so that we can do a strcat later.
			setCursorIndexInternal(0);
		}
		else if ( stringLength > writableCharsRemainingInternal() )
		{
			// Fit the string in right at the end of the buffer.
			// We need space to write the string and a terminator.
			setCursorIndexInternal(m_Size - stringLength - 1);
		}

		return strcat(string);
	}

	void StringBuilder::truncate(size_t length)
	{
		if ( !isValid() || length > m_Size - 1 || length > strlenInternal() )
		{
			return;
		}

		setCursorIndexInternal(length);
	}

	bool StringBuilder::vFormatInternal(char* cursor, const char* format, va_list args)
	{
		const size_t remainingSpace = m_Size - (cursor - m_Buffer);
		int result = vsnprintf_safe(cursor, remainingSpace, format, args);

		bool writtenSuccessfully = false;

		if ( result < 1 )
		{
			result = 0;
			m_Cursor = cursor;
		}
		else
		{
			if ( static_cast<size_t>(result) > remainingSpace - 1 )
			{
				result = remainingSpace - 1;
			}
			else
			{
				writtenSuccessfully = true;
			}

			m_Cursor = cursor + result;
		}

		return writtenSuccessfully;
	}
}
