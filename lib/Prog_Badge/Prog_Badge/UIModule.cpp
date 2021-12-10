#include <Arduino.h>
#include "UIModule.h"

namespace Badge
{
	namespace UIModule
	{
		static UIModuleResources StaticResourcesObject;

		UIModuleResources& resourcesObject()
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

		void setNextScreen(UIModuleResources::ScreenID id)
		{
			StaticResourcesObject.setNextScreen(id);
		}
	}
}
