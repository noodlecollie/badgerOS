#pragma once

#include <StringLib/StringBuilder.h>
#include <SerialConsole/Interpreter.h>
#include <SerialConsole/CommandArguments.h>

namespace Badge
{
	namespace Commands
	{
		SerialConsole::Interpreter::CommandResult btn(const SerialConsole::CommandArguments& args, StringLib::StringBuilder& output);
	}
}
