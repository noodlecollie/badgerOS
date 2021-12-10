#pragma once

#include <CoreUtil/TimeHelpers.h>
#include "UIModuleResources.h"

namespace Badge
{
	namespace UIModule
	{
		UIModuleResources& resourcesObject();

		void setup();
		void loop(CoreUtil::TimevalMs currentTime);

		UIModuleResources::ScreenID currentScreen();
		void setNextScreen(UIModuleResources::ScreenID id);
	}
}
