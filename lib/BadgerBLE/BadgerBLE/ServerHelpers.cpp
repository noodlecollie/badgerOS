#include <BadgerBLE/ServerHelpers.h>

namespace BadgerBLE
{
	namespace ServerHelpers
	{
		NimBLEService* createService(NimBLEServer& server, const ServiceSpec& spec)
		{
			NimBLEService* service = server.createService(spec.service().uuid);

			if ( !service )
			{
				return nullptr;
			}

			for ( size_t index = 0; index < spec.characteristicCount(); ++index )
			{
				service->createCharacteristic(spec[index].uuid, spec[index].attributes);
			}

			return service;
		}
	}
}
