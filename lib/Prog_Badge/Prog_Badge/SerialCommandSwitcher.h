#pragma once

#include <SerialConsole/Interpreter.h>

namespace Badge
{
	namespace SerialCommandSwitcher
	{
		SerialConsole::Interpreter::CommandResult ReceiveCommand(const char* input, StringLib::StringBuilder& output);
	}
}
