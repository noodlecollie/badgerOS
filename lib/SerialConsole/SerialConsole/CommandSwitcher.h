#pragma once

#include <cstddef>
#include <StringLib/StringBuilder.h>
#include "Interpreter.h"
#include "CommandArguments.h"

namespace SerialConsole
{
	class CommandSwitcher
	{
	public:
		using CommandCallback = Interpreter::CommandResult (*)(const CommandArguments&, StringLib::StringBuilder&);

		struct Command
		{
			const char* name;
			CommandCallback callback;
		};

		CommandSwitcher();

		void setCommandList(const Command* commandList, size_t commandCount);
		Interpreter::CommandResult receiveCommand(char* input, StringLib::StringBuilder& output);

	private:
		const Command* m_Commands = nullptr;
		size_t m_CommandCount = 0;
	};
}
