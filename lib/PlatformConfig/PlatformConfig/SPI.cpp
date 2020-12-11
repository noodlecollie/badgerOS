#include "SPI.h"

namespace PlatformConfig
{
	void spiSetup(const SPIConfig& config)
	{
		SPI.setDataMode(config.dataMode);
		SPI.setBitOrder(config.bitOrder);

		if ( config.clockMode == SPIConfig::ClockRateMode::Frequency )
		{
			SPI.setFrequency(config.clockValue);
		}
		else
		{
			SPI.setClockDivider(config.clockValue);
		}
	}
}
