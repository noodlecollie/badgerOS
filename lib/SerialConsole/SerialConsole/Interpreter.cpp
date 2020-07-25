#include <Arduino.h>
#include <cstring>
#include "Interpreter.h"

namespace SerialConsole
{
	void Interpreter::setReadBuffer(char* buffer, size_t size)
	{
		m_ReadBuffer = Buffer(buffer, size);
	}

	void Interpreter::setWriteBuffer(char* buffer, size_t size)
	{
		m_WriteBuffer = Buffer(buffer, size);
	}

	const Interpreter::CommandCallback& Interpreter::commandCallback() const
	{
		return m_Callback;
	}

	void Interpreter::setCommandCallback(const CommandCallback& callback)
	{
		m_Callback = callback;
	}

	void Interpreter::loop()
	{
		if ( !m_ReadBuffer.isValid() || !m_WriteBuffer.isValid() )
		{
			return;
		}

		if ( m_State == State::Reading )
		{
			loopRead();
		}
		else
		{
			loopWrite();
		}
	}

	void Interpreter::loopRead()
	{
		for ( int availableBytes = Serial.available(); availableBytes > 0; --availableBytes )
		{
			const char ch = static_cast<char>(Serial.read());
			m_ReadBuffer.appendChar(ch);

			if ( m_ReadBuffer.charsRemaining() < 1 && ch != '\n' )
			{
				// We filled up the entire buffer (bar the terminator) and
				// there was no newline. This equates to a read buffer overflow,
				// since we can't execute the full command.

				m_ReadBuffer.clear();
				m_WriteBuffer.clear();
				m_WriteBuffer.strcat("Read buffer overflow!\n");
				m_State = State::Writing;
				return;
			}

			if ( ch == '\n' )
			{
				// We read a full line. Execute the command.
				// This call terminates the command string.
				eraseCommandTrailingNewlines();
				invokeCallback();

				if ( m_WriteBuffer.strlen() > 0 )
				{
					m_State = State::Writing;
				}

				return;
			}
		}
	}

	void Interpreter::loopWrite()
	{
		int availableBytes = Serial.availableForWrite();

		if ( availableBytes < 1 )
		{
			return;
		}

		if ( !m_WriteCursor )
		{
			m_WriteCursor = m_WriteBuffer.string();
		}

		const int bytesToWrite = m_WriteBuffer.strlen() - (m_WriteCursor - m_WriteBuffer.string());
		bool lastWrite = false;

		if ( availableBytes >= bytesToWrite )
		{
			availableBytes = bytesToWrite;
			lastWrite = true;
		}

		for ( ; availableBytes > 0; --availableBytes )
		{
			Serial.write(static_cast<uint8_t>(*(m_WriteCursor++)));
		}

		if ( lastWrite )
		{
			m_WriteCursor = nullptr;
			m_WriteBuffer.clear();
			m_State = State::Reading;
		}
	}

	void Interpreter::invokeCallback()
	{
		m_WriteBuffer.clear();

		if ( m_Callback )
		{
			m_Callback(m_ReadBuffer.string(), m_WriteBuffer);
		}

		m_ReadBuffer.clear();
	}

	void Interpreter::eraseCommandTrailingNewlines()
	{
		char* cursor = m_ReadBuffer.mutableCursor() - 1;
		char* const begin = m_ReadBuffer.mutableBegin();

		while ( cursor >= begin )
		{
			if ( *cursor == '\n' || *cursor == '\r' )
			{
				*(cursor--) = '\0';
			}
			else
			{
				break;
			}
		}

		m_ReadBuffer.updateCursor();
	}
}
