#pragma once

class NimBLEServer;
class NimBLEService;

namespace Badge
{
	class IBadgeBLEService
	{
	public:
		virtual ~IBadgeBLEService() = default;

		virtual NimBLEService* initialise(NimBLEServer& server) = 0;
		virtual void loop(NimBLEServer& server) = 0;
	};
}
