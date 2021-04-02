#pragma once

class NimBLEService;

namespace Badge
{
	class BadgeBLEServer
	{
	public:
		BadgeBLEServer();

		void initialise();

		bool isAdvertisingEnabled() const;
		void setAdvertisingEnabled(bool enabled);

	private:
		char m_Name[32];

		NimBLEService* m_EchoService = nullptr;
	};
}
