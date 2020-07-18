#pragma once

#include <BadgerUI/FontDirectory.h>

namespace Badge
{
	namespace UIModule
	{
		const BadgerUI::FontDirectory& fontDirectory();

		void setup();
		void loop();
	}
}
