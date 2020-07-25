#pragma once

#include <cstddef>
#include <cstdarg>
#include <cstdint>

namespace StringLib
{
	class StringBuilder
	{
	public:
		// The buffer passed in is not owned by the StringBuilder. It is assumed that this
		// buffer will exist for the entire time the StringBuilder is in use.
		StringBuilder(char* buffer, size_t length);

		inline bool isValid() const
		{
			return m_Buffer != nullptr && m_Size > 0;
		}

		// Constant time.
		inline size_t strlen() const
		{
			return isValid() ? strlenInternal() : 0;
		}

		// Not including terminator.
		inline size_t charsRemaining() const
		{
			return isValid() ? writableCharsRemainingInternal() : 0;
		}

		// Including terminator.
		inline size_t bufferSizeRemaining() const
		{
			return isValid() ? writableCharsRemainingInternal() + 1 : 0;
		}

		inline const char* string() const
		{
			return isValid() ? m_Buffer : nullptr;
		}

		inline size_t totalBufferSize() const
		{
			return isValid() ? m_Size : 0;
		}

		// Be careful with this function - writing to the buffer manually will not update the internal state.
		// Call updateCursor() after modification.
		// Ensure that this pointer stays within the range [mutableBegin mutableEnd),
		// and that any modifications via the cursor keep the string terminated.
		inline char* mutableCursor()
		{
			return isValid() ? m_Cursor : nullptr;
		}

		inline char* mutableBegin()
		{
			return isValid() ? m_Buffer : nullptr;
		}

		inline char* mutableEnd()
		{
			return isValid() ? m_Buffer + m_Size : nullptr;
		}

		void updateCursor();

		// All functions that operate on the internal string buffer will ensure that it remains properly terminated.

		// The following functions return true if the given data was written without truncation.
		// The number of characters written can be computed efficiently by calling strlen()
		// before and after the operation.
		bool strcat(const char* string);
		bool strcpy(const char* string);
		bool snprintf(const char* format, ...);
		bool vsnprintf(const char* format, va_list args);
		bool appendFormat(const char* format, ...);
		bool appendVFormat(const char* format, va_list args);
		bool appendRepeatedChar(char ch, size_t count);

		void clear();

		bool endsWith(const char* suffix) const;

		// Operates the same way as strcat, except that if there is not enough free space
		// on the end of the buffer for the new string, it will overwrite existing characters.
		// For example, calling this function with the string "End" on an existing buffer
		// comprised of { 'S', 't', 'a', 'r', 't', '\0', '\0' } will result in
		// { 'S', 't', 'a', 'E', 'n', 'd', '\0' }.
		// This function returns false if the string is too long for the buffer in the first
		// place - in this case, it will begin at the start of the buffer and as many
		// characters will be written as possible. Otherwise, it will return true.
		bool strcatWithOverwrite(const char* string);

		// If length is greater than the current length, does nothing.
		// If length is less than the current length, truncates the string to be
		// the specified number of characters long (not including the terminator).
		void truncate(size_t length);

		inline operator const char*() const
		{
			return string();
		}

	private:
		// Validity is not checked for the following internal functions:
		inline size_t strlenInternal() const
		{
			return m_Cursor - m_Buffer;
		}

		inline size_t writableCharsRemainingInternal() const
		{
			return m_Size - strlenInternal() - 1;
		}

		// Assumes index is in range.
		inline void setCursorIndexInternal(size_t index)
		{
			m_Cursor = m_Buffer + index;
			*m_Cursor = '\0';
		}

		bool vFormatInternal(char* cursor, const char* format, va_list args);

		char* m_Buffer = nullptr;
		size_t m_Size = 0;

		// Points at the terminator of the existing string.
		char* m_Cursor = nullptr;
	};

	inline StringBuilder& operator <<(StringBuilder& builder, const char* str)
	{
		builder.strcat(str);
		return builder;
	}

	inline StringBuilder& operator <<(StringBuilder& builder, uint32_t value)
	{
		builder.appendFormat("%u", value);
		return builder;
	}

	inline StringBuilder& operator <<(StringBuilder& builder, int32_t value)
	{
		builder.appendFormat("%d", value);
		return builder;
	}

	inline StringBuilder& operator <<(StringBuilder& builder, float value)
	{
		builder.appendFormat("%f", value);
		return builder;
	}
}
