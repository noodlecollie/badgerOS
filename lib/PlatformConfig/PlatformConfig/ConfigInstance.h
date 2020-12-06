#pragma once

#include <PlatformConfig/ConfigArgs.h>
#include <PlatformConfig/ConfigData.h>

namespace PlatformConfig
{
	class ConfigInstance
	{
	public:
		ConfigInstance(const ConfigArgs& args, const ConfigData& data) :
			m_Args(args),
			m_Data(data)
		{
		}

		const ConfigArgs& args() const
		{
			return m_Args;
		}

		const ConfigData& data() const
		{
			return m_Data;
		}

	private:
		const ConfigArgs& m_Args;
		const ConfigData& m_Data;
	};
}
