#include <StringLib/StringUtils.h>
#include <CoreUtil/ArrayUtil.h>
#include "SerialCommandSwitcher.h"

namespace Badge
{
	namespace SerialCommandSwitcher
	{
		using StaticCommandCallback = SerialConsole::Interpreter::CommandResult (*)(const char*, StringLib::StringBuilder&);

		struct CommandEntry
		{
			const char* name;
			StaticCommandCallback callback;
		};

		static const CommandEntry COMMANDS[] =
		{
			{
				"nop",
				[](const char*, StringLib::StringBuilder&)
				{
					return SerialConsole::Interpreter::CommandResult::Completed;
				}
			}
		};

		SerialConsole::Interpreter::CommandResult ReceiveCommand(const char* input, StringLib::StringBuilder& output)
		{
			static constexpr size_t MAX_COMMAND_NAME_LENGTH = 31;
			static char cmdNameBuffer[MAX_COMMAND_NAME_LENGTH + 1];

			const char* const endOfCmdName = StringLib::firstDelimiter(input, ' ');
			const size_t cmdNameLength = endOfCmdName - input;

			if ( cmdNameLength < 1 )
			{
				output.sprintf("No command name was provided.\n");
				return SerialConsole::Interpreter::CommandResult::Completed;
			}

			if ( cmdNameLength > MAX_COMMAND_NAME_LENGTH )
			{
				output.sprintf("Provided command name exceeded max length of %u characters.\n", MAX_COMMAND_NAME_LENGTH);
				return SerialConsole::Interpreter::CommandResult::Completed;
			}

			StringLib::strncpy_safe(cmdNameBuffer, sizeof(cmdNameBuffer), input, cmdNameLength);

			for ( uint32_t index = 0; index < CoreUtil::arraySize(COMMANDS); ++index )
			{
				if ( StringLib::equal(COMMANDS[index].name, cmdNameBuffer) )
				{
					// TODO: Break input up into argc/argv and pass this instead.
					return COMMANDS[index].callback(input, output);
				}
			}

			output.sprintf("Command '%s' was not found.\n", cmdNameBuffer);
			return SerialConsole::Interpreter::CommandResult::Completed;
		}
	}
}
