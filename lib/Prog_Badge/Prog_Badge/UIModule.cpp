#include <Arduino.h>
#include "UIModule.h"

namespace Badge
{
	namespace UIModule
	{
		static constexpr CoreUtil::TimevalMs UPDATE_INTERVAL_MS = 100;
		static UIModuleResources StaticResourcesObject;
		static CoreUtil::TimevalMs LastUpdate = 0;

		const UIModuleResources& resourcesObject()
		{
			return StaticResourcesObject;
		}

		void setup()
		{
			StaticResourcesObject.setup();
		}

		void loop()
		{
			const CoreUtil::TimevalMs currentTime = millis();

			if ( currentTime - LastUpdate < UPDATE_INTERVAL_MS )
			{
				return;
			}

			StaticResourcesObject.loop(currentTime);
			LastUpdate = currentTime;
		}
	}
}
