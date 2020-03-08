#pragma once

namespace ESP32HAL
{
	struct SerialConfig
	{
		unsigned long baudRate = 115200;
	};

	struct InitConfig
	{
		SerialConfig serial;
	};
}
