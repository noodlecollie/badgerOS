#include "Echo.h"

namespace Badge
{
	namespace Commands
	{
		SerialConsole::Interpreter::CommandResult echo(const SerialConsole::CommandArguments& args, StringLib::StringBuilder& output)
		{
			for ( uint32_t index = 1; index < args.argc(); ++index )
			{
				if ( index > 1 )
				{
					output.strcat(" ");
				}

				output.strcat(args.argv(index));
				output.strcat("\r\n");
			}

			return SerialConsole::Interpreter::CommandResult::Completed;
		}
	}
}
