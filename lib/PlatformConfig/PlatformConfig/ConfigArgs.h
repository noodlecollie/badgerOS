#pragma once

#include <PlatformConfig/SPI.h>

namespace PlatformConfig
{
	enum class DisplayType
	{
		None = 0,
		SSD1351,
		InkyImpression
	};

	// Per-project config
	struct ConfigArgs
	{
		DisplayType display = DisplayType::None;
		const SPIConfig* userSPIConfig = nullptr;
	};
}
