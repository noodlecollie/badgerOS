#pragma once

#include <Input/ButtonInputRecorder.h>

namespace Badge
{
	namespace InputModule
	{
		Input::ButtonInputRecorder& Buttons();

		void setup();
		void loop();
	}
}
