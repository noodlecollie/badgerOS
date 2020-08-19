#pragma once

#include <StringLib/StringBuilder.h>
#include <SerialConsole/Interpreter.h>
#include <SerialConsole/CommandArguments.h>

namespace Badge
{
	namespace Commands
	{
		SerialConsole::Interpreter::CommandResult echo(const SerialConsole::CommandArguments& args, StringLib::StringBuilder& output);
	}
}
