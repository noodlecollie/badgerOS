#include <PlatformConfig/PlatformConfigObject.h>

namespace PlatformConfig
{
	void PlatformConfigObject::initialise(const ConfigArgs& args)
	{
		m_ConfigArgs = args;
		initialiseDelegated(m_ConfigArgs);
	}

	const ConfigArgs& PlatformConfigObject::args() const
	{
		return m_ConfigArgs;
	}
}
