#pragma once

#include <cstddef>
#include <functional>
#include <StringLib/StringBuilder.h>

namespace SerialConsole
{
	class Interpreter
	{
	public:
		enum CommandResult
		{
			InProgress,
			Completed
		};

		using CommandCallback = std::function<CommandResult(char*, StringLib::StringBuilder&)>;

		void setReadBuffer(char* buffer, size_t size);
		void setWriteBuffer(char* buffer, size_t size);

		const CommandCallback& commandCallback() const;
		void setCommandCallback(const CommandCallback& callback);

		void loop();

	private:
		using Buffer = StringLib::StringBuilder;

		enum State
		{
			Reading,
			Writing
		};

		void loopRead();
		void loopWrite();
		void eraseCommandTrailingNewlines();

		// Returns true if the command completed.
		// If false is returned, continueCommand() should be called again next loop().
		bool initiateCommand();
		bool continueCommand();

		void prepareCommand();
		void invokeCommand();
		void completeCommand();

		Buffer m_ReadBuffer;
		Buffer m_WriteBuffer;
		const char* m_WriteCursor = nullptr;
		CommandCallback m_Callback;
		CommandResult m_LastCommandResult = CommandResult::Completed;
		State m_State = State::Reading;
	};

	template<size_t READBUF, size_t WRITEBUF>
	class StaticallyAllocatedInterpreter : public Interpreter
	{
	public:
		static constexpr size_t READ_BUFFER_SIZE = READBUF;
		static constexpr size_t WRITE_BUFFER_SIZE = WRITEBUF;

		inline StaticallyAllocatedInterpreter() :
			Interpreter()
		{
			setReadBuffer(m_ReadBufferMem, sizeof(m_ReadBufferMem));
			setWriteBuffer(m_WriteBufferMem, sizeof(m_WriteBufferMem));
		}

	private:
		char m_ReadBufferMem[READ_BUFFER_SIZE];
		char m_WriteBufferMem[WRITE_BUFFER_SIZE];
	};
}
