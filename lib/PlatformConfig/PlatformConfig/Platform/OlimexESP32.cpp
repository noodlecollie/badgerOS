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
		.chipSelectPin = 5,
		.resetPin = 27,
		.dataCommandPin = 16
	};

	namespace OlimexESP32
	{
		void getConfig(Config& config)
		{
			memset(&config, 0, sizeof(config));

			config.ssd1351Config = &SSD1351_CONFIG;
			config.serialConfig = &SERIAL_CONFIG;
			config.spiConfig = &SPI_CONFIG;
			config.spiPinConfig = &SPI_PIN_CONFIG_VSPI;
		}
	}
}
