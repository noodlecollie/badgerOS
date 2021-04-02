#pragma once

#include <Prog_Badge/Bluetooth/BadgeBLEServer.h>

namespace Badge
{
	namespace BluetoothModule
	{
		BadgeBLEServer& bleServer();

		void setup();
		void loop();
	}
}
