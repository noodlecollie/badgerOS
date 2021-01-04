#include <Plat_OlimexESP32/ConfigObject.h>

namespace OlimexESP32
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
		.resetPin = 27,
		.dataCommandPin = 16
	};

	static constexpr PlatformConfig::ChipSelectConfig CHIP_SELECT_CONFIG =
	{
		.displayCSPin = 5
	};

	static constexpr InkyImpression::InkyDriver::Config INKY_IMPRESSION_CONFIG =
	{
		.resetPin = 27,
		.dataCommandPin = 16,
		.busyPin = 35
	};

	ConfigObject::ConfigObject() :
		PlatformConfig::PlatformConfigObject(),
		m_SerialConfig(PlatformConfig::SERIAL_CONFIG_DEFAULT),
		m_SPIConfig(PlatformConfig::SPI_CONFIG_DEFAULT),
		m_SPIPinConfig(SPI_PIN_CONFIG_VSPI),
		m_ChipSelectConfig(CHIP_SELECT_CONFIG),
		m_SSD1351Config(SSD1351_CONFIG),
		m_InkyConfig(INKY_IMPRESSION_CONFIG)
	{
	}

	void ConfigObject::initialiseDelegated(const PlatformConfig::ConfigArgs& args)
	{
		if ( args.userSPIConfig )
		{
			m_SPIConfig = *args.userSPIConfig;
		}
	}

	void ConfigObject::getElementDelegated(const PlatformConfig::SerialConfig*& out) const
	{
		out = &m_SerialConfig;
	}

	void ConfigObject::getElementDelegated(const PlatformConfig::SPIConfig*& out) const
	{
		out = &m_SPIConfig;
	}

	void ConfigObject::getElementDelegated(const PlatformConfig::SPIPinConfig*& out) const
	{
		out = &m_SPIPinConfig;
	}

	void ConfigObject::getElementDelegated(const PlatformConfig::ChipSelectConfig*& out) const
	{
		out = &m_ChipSelectConfig;
	}

	void ConfigObject::getElementDelegated(const SSD1351::OLEDDriver::Config*& out) const
	{
		if ( args().display == PlatformConfig::DisplayType::SSD1351 )
		{
			out = &m_SSD1351Config;
		}
	}

	void ConfigObject::getElementDelegated(const InkyImpression::InkyDriver::Config*& out) const
	{
		if ( args().display == PlatformConfig::DisplayType::InkyImpression )
		{
			out = &m_InkyConfig;
		}
	}
}
