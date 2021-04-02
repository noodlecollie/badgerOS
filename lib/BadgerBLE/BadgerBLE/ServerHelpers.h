#pragma once

#include <cstddef>
#include <NimBLEServer.h>
#include <BadgerBLE/GATTDefs.h>
#include <BadgerBLE/ServiceSpec.h>

namespace BadgerBLE
{
	namespace ServerHelpers
	{
		NimBLEService* createService(NimBLEServer& server, const ServiceSpec& spec);
	}
}
