#include <Plat_OlimexESP32/OlimexESP32.h>
#include <Plat_OlimexESP32/ConfigObject.h>

namespace OlimexESP32
{
	PlatformConfig::PlatformConfigObject* getConfigObject()
	{
		static ConfigObject instance;
		return &instance;
	}
}
