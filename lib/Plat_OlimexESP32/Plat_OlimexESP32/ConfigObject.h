#pragma once

#include <PlatformConfig/PlatformConfigObject.h>

namespace OlimexESP32
{
	class ConfigObject : public PlatformConfig::PlatformConfigObject
	{
	public:
		ConfigObject();

	protected:
		void initialiseDelegated(const PlatformConfig::ConfigArgs& args) override;
		void getElementDelegated(const PlatformConfig::SerialConfig*& out) const override;
		void getElementDelegated(const PlatformConfig::SPIConfig*& out) const override;
		void getElementDelegated(const PlatformConfig::SPIPinConfig*& out) const override;
		void getElementDelegated(const PlatformConfig::ChipSelectConfig*& out) const override;
		void getElementDelegated(const SSD1351::OLEDDriver::Config*& out) const override;
		void getElementDelegated(const InkyImpression::InkyDriver::Config*& out) const override;

	private:
		PlatformConfig::SerialConfig m_SerialConfig;
		PlatformConfig::SPIConfig m_SPIConfig;
		PlatformConfig::SPIPinConfig m_SPIPinConfig;
		PlatformConfig::ChipSelectConfig m_ChipSelectConfig;
		SSD1351::OLEDDriver::Config m_SSD1351Config;
		InkyImpression::InkyDriver::Config m_InkyConfig;
	};
}
