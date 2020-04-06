#include <Prog_SanityTest/SanityTest.h>
#include <PlatformConfig/Platform/OlimexESP32.h>

void setup()
{
	SanityTest::setup(&PlatformConfig::OlimexESP32::getConfig);
}

void loop()
{
	SanityTest::loop();
}
