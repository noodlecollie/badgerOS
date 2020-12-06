#pragma once

namespace PlatformConfig
{
	enum class DisplayType
	{
		None = 0,
		SSD1351,
		InkyImpression
	};

	struct ConfigArgs
	{
		DisplayType display = DisplayType::None;
	};
}
