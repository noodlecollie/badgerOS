#pragma once

#include <cstdint>

namespace InkyImpression
{
	class Driver
	{
	public:
		struct Config
		{
			uint8_t resetPin;
			uint8_t dataCommandPin;
			uint8_t busyPin;
		};
	};
}
