#include <Arduino.h>
#include "UIModule.h"

namespace Badge
{
	namespace UIModule
	{
		static UIModuleResources StaticResourcesObject;

		const UIModuleResources& resourcesObject()
		{
			return StaticResourcesObject;
		}

		void setup()
		{
			StaticResourcesObject.setup();
		}

		void loop(CoreUtil::TimevalMs currentTime)
		{
			StaticResourcesObject.loop(currentTime);
		}

		UIModuleResources::ScreenID currentScreen()
		{
			return StaticResourcesObject.currentScreen();
		}

		void setCurrentScreen(UIModuleResources::ScreenID id)
		{
			StaticResourcesObject.setCurrentScreen(id);
		}
	}
}
