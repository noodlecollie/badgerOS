#include "InputModule.h"

namespace Badge
{
	namespace InputModule
	{
		static Input::ButtonInputRecorder ButtonInput;

		Input::ButtonInputRecorder& buttons()
		{
			return ButtonInput;
		}

		void setup()
		{
		}

		void loop()
		{
			ButtonInput.advanceFrame();
		}
	}
}
