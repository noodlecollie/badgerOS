#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>
#include "Badge.h"

#include "Init/SerialInit.h"

namespace Badge
{
	static inline void initSubsystems()
	{
		using namespace PlatformConfig;

		initialiseSubsystem(&Config::serialConfig, &serialInit);

		Serial.printf("====================================\n");
		Serial.printf("         BadgerOS booting...        \n");
		Serial.printf("====================================\n");
		Serial.printf("Version %s\n", Versions::VERSION_STRING_FULL);
	}

	void setup()
	{
		initSubsystems();
	}

	void loop()
	{
	}
}
