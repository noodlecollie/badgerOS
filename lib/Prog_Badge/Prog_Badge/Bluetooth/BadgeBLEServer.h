#pragma once

class NimBLEService;

namespace Badge
{
	class BadgeBLEServer
	{
	public:
		BadgeBLEServer();

		void initialise();
		void startAdvertising();

	private:
		char m_Name[32];

		NimBLEService* m_EchoService = nullptr;
	};
}
