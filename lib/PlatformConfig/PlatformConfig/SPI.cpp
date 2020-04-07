#include "SPI.h"

namespace PlatformConfig
{
	void spiSetup(const SPIConfig& config)
	{
		SPI.setDataMode(config.dataMode);
		SPI.setBitOrder(config.bitOrder);
		SPI.setClockDivider(config.clockDivider);
	}
}
