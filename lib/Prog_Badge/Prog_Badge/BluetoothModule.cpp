#include <Prog_Badge/BluetoothModule.h>
#include <Prog_Badge/Bluetooth/BadgeBLEServer.h>

namespace Badge
{
	static BadgeBLEServer Server;

	namespace BluetoothModule
	{
		BadgeBLEServer& bleServer()
		{
			return Server;
		}

		void setup()
		{
			Server.initialise();
		}

		void loop()
		{
			Server.loop();
		}
	}
}
