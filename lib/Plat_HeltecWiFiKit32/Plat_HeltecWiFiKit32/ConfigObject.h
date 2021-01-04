#pragma once

#include <PlatformConfig/PlatformConfigObject.h>

namespace HeltecWiFiKit32
{
	class ConfigObject : public PlatformConfig::PlatformConfigObject
	{
	public:
		ConfigObject();

	protected:
		void initialiseDelegated(const PlatformConfig::ConfigArgs& args) override;
		void getElementDelegated(const SerialConfig*& out) const override;
		void getElementDelegated(const SPIConfig*& out) const override;
		void getElementDelegated(const SPIPinConfig*& out) const override;
		void getElementDelegated(const ChipSelectConfig*& out) const override;
		void getElementDelegated(const SSD1351Config*& out) const override;

	private:
		SerialConfig m_SerialConfig;
		SPIConfig m_SPIConfig;
		SPIPinConfig m_SPIPinConfig;
		ChipSelectConfig m_ChipSelectConfig;
		SSD1351Config m_SSD1351Config;
	};
}
