#include <Prog_Badge/Commands/BluetoothCtl.h>
#include <StringLib/StringUtils.h>
#include <Prog_Badge/BluetoothModule.h>

namespace Badge
{
	namespace Commands
	{
		SerialConsole::Interpreter::CommandResult bluetoothCtl(const SerialConsole::CommandArguments& args, StringLib::StringBuilder& output)
		{
			if ( args.argc() != 2 )
			{
				output.sprintf(
					"Usage: %s <on|off>\r\n"
					"Bluetooth advertising is currently %s\r\n",
					args.argv(0),
					BluetoothModule::bleServer().isAdvertisingEnabled() ? "on" : "off");

				return SerialConsole::Interpreter::CommandResult::Completed;
			}

			const char* action = args.argv(1);
			BadgeBLEServer& server = BluetoothModule::bleServer();

			if ( StringLib::equal(action, "on") )
			{
				server.setAdvertisingEnabled(true);
				output.sprintf("Bluetooth advertising turned on\r\n");
			}
			else if ( StringLib::equal(action, "off") )
			{
				server.setAdvertisingEnabled(false);
				output.sprintf("Bluetooth advertising turned off\r\n");
			}
			else
			{
				output.sprintf("Unrecognised argument '%s'\r\n", action);
			}

			return SerialConsole::Interpreter::CommandResult::Completed;
		}
	}
}
