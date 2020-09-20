#pragma once

#include <CoreUtil/TimeHelpers.h>
#include "UIModuleResources.h"

namespace Badge
{
	namespace UIModule
	{
		const UIModuleResources& resourcesObject();

		void setup();
		void loop(CoreUtil::TimevalMs currentTime);

		UIModuleResources::ScreenID currentScreen();
		void setCurrentScreen(UIModuleResources::ScreenID id);
	}
}
