#pragma once

#include <Input/ButtonInputRecorder.h>

namespace Badge
{
	namespace InputModule
	{
		Input::ButtonInputRecorder& buttons();

		void setup();
		void loop();
	}
}
