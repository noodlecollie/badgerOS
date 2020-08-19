#include <StringLib/StringUtils.h>
#include "CommandSwitcher.h"

namespace SerialConsole
{
	CommandSwitcher::CommandSwitcher()
	{
	}

	void CommandSwitcher::setCommandList(const Command* commandList, size_t commandCount)
	{
		if ( commandList && commandCount > 0 )
		{
			m_Commands = commandList;
			m_CommandCount = commandCount;
		}
	}

	Interpreter::CommandResult CommandSwitcher::receiveCommand(char* input, StringLib::StringBuilder& output)
	{
		CommandArguments args(input);

		if ( args.argc() < 1 )
		{
			output.sprintf("No command name was provided.\r\n");
			return SerialConsole::Interpreter::CommandResult::Completed;
		}

		const char* commandName = args.argv(0);

		for ( uint32_t index = 0; index < m_CommandCount; ++index )
		{
			const Command& cmd = m_Commands[index];

			if ( StringLib::equal(cmd.name, commandName) )
			{
				if ( cmd.callback )
				{
					return cmd.callback(args, output);
				}
				else
				{
					// Shouldn't happen:
					output.sprintf("Command '%s' had no callback set.\r\n", commandName);
					return SerialConsole::Interpreter::CommandResult::Completed;
				}
			}
		}

		output.sprintf("Command '%s' was not found.\r\n", commandName);
		return SerialConsole::Interpreter::CommandResult::Completed;
	}
}
