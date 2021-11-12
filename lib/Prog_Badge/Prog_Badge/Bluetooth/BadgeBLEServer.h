#pragma once

#include <Prog_Badge/Bluetooth/Services/EchoService.h>

class BLEService;

namespace Badge
{
	class BadgeBLEServer
	{
	public:
		BadgeBLEServer();

		void initialise();
		void loop();

		bool isAdvertisingEnabled() const;
		void setAdvertisingEnabled(bool enabled);

	private:
		void setUpService(NimBLEService* service);

		char m_Name[32];

		BLEServices::EchoService m_EchoService;
	};
}
