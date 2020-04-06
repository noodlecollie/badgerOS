#include <Prog_SanityTest/SanityTest.h>
#include <PlatformConfig/Platform/HeltecWiFiKit32.h>

void setup()
{
	SanityTest::setup(&PlatformConfig::HeltecWiFiKit32::getConfig);
}

void loop()
{
	SanityTest::loop();
}
