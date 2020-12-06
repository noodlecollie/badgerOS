#include <cstring>
#include "HeltecWiFiKit32.h"

namespace PlatformConfig
{
	static constexpr SerialConfig SERIAL_CONFIG = SERIAL_CONFIG_DEFAULT;
	static constexpr SPIConfig SPI_CONFIG = SPI_CONFIG_DEFAULT;

	static constexpr SPIPinConfig SPI_PIN_CONFIG_VSPI =
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

	static constexpr ChipSelectConfig CHIP_SELECT_CONFIG =
	{
		.displayCSPin = 5
	};

	namespace HeltecWiFiKit32
	{
		void getConfig(const ConfigArgs& args, ConfigData& data)
		{
			memset(&data, 0, sizeof(data));

			if ( args.display == DisplayType::SSD1351 )
			{
				data.displayConfig.ssd1351 = &SSD1351_CONFIG;
			}

			data.serialConfig = &SERIAL_CONFIG;
			data.spiConfig = &SPI_CONFIG;
			data.chipSelectConfig = &CHIP_SELECT_CONFIG;
		}
	}
}
