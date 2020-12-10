#pragma once

#include <PlatformConfig/ConfigArgs.h>
#include <PlatformConfig/ConfigData.h>

namespace PlatformConfig
{
	class ConfigInstance
	{
	public:
		inline ConfigInstance(const ConfigArgs& args, const ConfigData& data) :
			m_Args(args),
			m_Data(data)
		{
		}

		inline const ConfigArgs& args() const
		{
			return m_Args;
		}

		inline const ConfigData& data() const
		{
			return m_Data;
		}

		// Helpers:

		inline const SSD1351::OLEDDriver::Config* ssd1351Config() const
		{
			return m_Args.display == DisplayType::SSD1351
				? m_Data.displayConfig.ssd1351
				: nullptr;
		}

		inline const InkyImpression::InkyDriver::Config* inkyImpressionConfig() const
		{
			return m_Args.display == DisplayType::InkyImpression
				? m_Data.displayConfig.inkyImpression
				: nullptr;
		}

	private:
		const ConfigArgs& m_Args;
		const ConfigData& m_Data;
	};
}
