#pragma once

#include <cstdint>

namespace InkyImpression
{
	class InkyDriver
	{
	public:
		struct Config
		{
			uint8_t resetPin;
			uint8_t dataCommandPin;
			uint8_t busyPin;
		};

		void initialise(const Config& cfg);
	};

	extern InkyDriver Driver;
}
