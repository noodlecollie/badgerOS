#include <Arduino.h>
#include <CoreUtil/TimeHelpers.h>
#include <StringLib/StringUtils.h>
#include "../InputModule.h"
#include "Btn.h"

namespace Badge
{
	namespace Commands
	{
		static constexpr CoreUtil::TimevalMs BUTTON_PRESS_INTERVAL_MS = 200;

		static int32_t PressedButtonID = -1;
		static CoreUtil::TimevalMs LastPressTime = 0;

		static SerialConsole::Interpreter::CommandResult handleInputInProgress(const SerialConsole::CommandArguments& args, StringLib::StringBuilder& output)
		{
			const CoreUtil::TimevalMs now = millis();

			if ( now - LastPressTime >= BUTTON_PRESS_INTERVAL_MS )
			{
				output.appendFormat("Button %d released @ %u.\r\n", PressedButtonID, now);

				InputModule::buttons().setReleased(1 << PressedButtonID);
				PressedButtonID = -1;
				LastPressTime = 0;

				return SerialConsole::Interpreter::CommandResult::Completed;
			}

			return SerialConsole::Interpreter::CommandResult::InProgress;
		}

		static SerialConsole::Interpreter::CommandResult initiateInput(int32_t buttonID, StringLib::StringBuilder& output)
		{
			LastPressTime = millis();
			PressedButtonID = buttonID;
			InputModule::buttons().setPressed(1 << PressedButtonID);

			output.sprintf("Button %d pressed @ %u.\r\n", PressedButtonID, LastPressTime);

			return SerialConsole::Interpreter::CommandResult::InProgress;
		}

		SerialConsole::Interpreter::CommandResult btn(const SerialConsole::CommandArguments& args, StringLib::StringBuilder& output)
		{
			static constexpr int32_t MAX_BUTTON_INDEX = (sizeof(uint32_t) * 8) - 1;

			if ( PressedButtonID >= 0 )
			{
				return handleInputInProgress(args, output);
			}

			if ( args.argc() != 2 )
			{
				// Should always have at least 1 argument, but just in case:
				const char* const cmdName = args.argc() > 0 ? args.argv(0) : "ERROR";

				output.sprintf("Expected command: %s <id>\r\n", cmdName);
				return SerialConsole::Interpreter::CommandResult::Completed;
			}

			int32_t buttonID = 0;

			if ( !StringLib::toInt(args.argv(1), buttonID) )
			{
				output.sprintf("Button ID '%s' was not a number.\r\n", args.argv(1));
				return SerialConsole::Interpreter::CommandResult::Completed;
			}

			if ( buttonID < 0 || buttonID > MAX_BUTTON_INDEX )
			{
				output.sprintf("Button ID %d was not valid - should be between 0 and %d.\r\n", buttonID, MAX_BUTTON_INDEX);
				return SerialConsole::Interpreter::CommandResult::Completed;
			}

			return initiateInput(buttonID, output);
		}
	}
}
