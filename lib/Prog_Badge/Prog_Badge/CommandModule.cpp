#include <CoreUtil/ArrayUtil.h>
#include <SerialConsole/Interpreter.h>
#include <SerialConsole/CommandSwitcher.h>
#include "CommandModule.h"

#include <Prog_Badge/Commands/Echo.h>
#include <Prog_Badge/Commands/Btn.h>
#include <Prog_Badge/Commands/BluetoothCtl.h>

namespace Badge
{
	namespace CommandModule
	{
		static const SerialConsole::CommandSwitcher::Command Commands[] =
		{
			{ "echo", &Commands::echo },
			{ "btn", &Commands::btn },
			{ "btctl", &Commands::bluetoothCtl }
		};

		static SerialConsole::StaticallyAllocatedInterpreter<128, 128> CommandInterpreter;
		static SerialConsole::CommandSwitcher CommandSwitcher;

		void setup()
		{
			CommandSwitcher.setCommandList(Commands, CoreUtil::arraySize(Commands));

			CommandInterpreter.setCommandCallback([](char* input, StringLib::StringBuilder& output)
			{
				return CommandSwitcher.receiveCommand(input, output);
			});
		}

		void loop()
		{
			CommandInterpreter.loop();
		}
	}
}
