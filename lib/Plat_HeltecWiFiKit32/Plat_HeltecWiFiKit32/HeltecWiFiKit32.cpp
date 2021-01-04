#include <Plat_HeltecWiFiKit32/HeltecWiFiKit32.h>
#include <Plat_HeltecWiFiKit32/ConfigObject.h>

namespace HeltecWiFiKit32
{
	PlatformConfig::PlatformConfigObject* getConfigObject()
	{
		static ConfigObject instance;
		return &instance;
	}
}
