#include <Plat_HeltecWiFiKit32/ConfigObject.h>

namespace HeltecWiFiKit32
{
	static constexpr PlatformConfig::SPIPinConfig SPI_PIN_CONFIG_VSPI =
	{
		.clockPin = 18,
		.misoPin = 19,
		.mosiPin = 23,
		.writeProtectPin = 22,
		.holdPin = 21
	};

	static constexpr SSD1351::OLEDDriver::Config SSD1351_CONFIG =
	{
		.resetPin = 36,
		.dataCommandPin = 17
	};

	static constexpr PlatformConfig::ChipSelectConfig CHIP_SELECT_CONFIG =
	{
		.displayCSPin = 5
	};

	ConfigObject::ConfigObject() :
		PlatformConfig::PlatformConfigObject(),
		m_SerialConfig(PlatformConfig::SERIAL_CONFIG_DEFAULT),
		m_SPIConfig(PlatformConfig::SPI_CONFIG_DEFAULT),
		m_SPIPinConfig(SPI_PIN_CONFIG_VSPI),
		m_ChipSelectConfig(CHIP_SELECT_CONFIG),
		m_SSD1351Config(SSD1351_CONFIG)
	{
	}

	void ConfigObject::initialiseDelegated(const PlatformConfig::ConfigArgs& args)
	{
		if ( args.userSPIConfig )
		{
			m_SPIConfig = *args.userSPIConfig;
		}
	}

	void ConfigObject::getElementDelegated(const SerialConfig*& out) const
	{
		out = &m_SerialConfig;
	}

	void ConfigObject::getElementDelegated(const SPIConfig*& out) const
	{
		out = &m_SPIConfig;
	}

	void ConfigObject::getElementDelegated(const SPIPinConfig*& out) const
	{
		out = &m_SPIPinConfig;
	}

	void ConfigObject::getElementDelegated(const ChipSelectConfig*& out) const
	{
		out = &m_ChipSelectConfig;
	}

	void ConfigObject::getElementDelegated(const SSD1351Config*& out) const
	{
		if ( args().display == PlatformConfig::DisplayType::SSD1351 )
		{
			out = &m_SSD1351Config;
		}
	}
}
