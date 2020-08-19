#pragma once

#include <cstddef>
#include <cstdint>

namespace SerialConsole
{
	// Assumes a mutable command string buffer.
	class CommandArguments
	{
	public:
		// Including command name.
		static constexpr size_t MAX_ARGS = 8;

		CommandArguments(char* command);

		CommandArguments(const CommandArguments& other) = delete;
		CommandArguments& operator =(const CommandArguments& other) = delete;

		inline size_t argc() const
		{
			return m_Argc;
		}

		inline const char* argv(uint32_t index) const
		{
			return index < m_Argc ? m_Argv[index] : nullptr;
		}

	private:
		void parseCommandString(char* command);

		const char* m_Argv[MAX_ARGS];
		size_t m_Argc = 0;
	};
}
