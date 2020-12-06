#include <cstring>
#include "OlimexESP32.h"

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
		.resetPin = 27,
		.dataCommandPin = 16
	};

	static constexpr InkyImpression::Driver::Config INKY_IMPRESSION_CONFIG =
	{
		.resetPin = 27,
		.dataCommandPin = 16,
		.busyPin = 33
	};

	static constexpr ChipSelectConfig CHIP_SELECT_CONFIG =
	{
		.displayCSPin = 5
	};

	static constexpr PowerConfig POWER_CONFIG =
	{
		.batteryLevelPin = 35,
		.externalPowerSensePin = 39
	};

	namespace OlimexESP32
	{
		void getConfig(const ConfigArgs& args, ConfigData& data)
		{
			memset(&data, 0, sizeof(data));

			switch ( args.display )
			{
				case DisplayType::SSD1351:
				{
					data.displayConfig.ssd1351 = &SSD1351_CONFIG;
					break;
				}

				case DisplayType::InkyImpression:
				{
					data.displayConfig.inkyImpression = &INKY_IMPRESSION_CONFIG;
					break;
				}

				default:
				{
					break;
				}
			}

			data.serialConfig = &SERIAL_CONFIG;
			data.spiConfig = &SPI_CONFIG;
			data.spiPinConfig = &SPI_PIN_CONFIG_VSPI;
			data.chipSelectConfig = &CHIP_SELECT_CONFIG;
			data.powerConfig = &POWER_CONFIG;
		}
	}
}
