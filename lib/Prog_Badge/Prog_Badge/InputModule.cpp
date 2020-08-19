#include "InputModule.h"

namespace Badge
{
	namespace InputModule
	{
		static Input::ButtonInputRecorder ButtonInput;

		Input::ButtonInputRecorder& Buttons()
		{
			return ButtonInput;
		}

		void setup()
		{

		}

		void loop()
		{

		}
	}
}
