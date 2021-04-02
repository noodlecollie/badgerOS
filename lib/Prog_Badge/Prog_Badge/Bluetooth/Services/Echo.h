#pragma once

#include <NimBLEDevice.h>
#include <BadgerBLE/GATTDefs.h>
#include <BadgerBLE/ServiceSpec.h>

namespace Badge
{
	namespace BluetoothServices
	{
		static constexpr BadgerBLE::ServiceDef SERVICE_ECHO =
		{
			.name = "badgeros.badge.bluetooth.services.echo",
			.uuid = "cd7c6eeb-c20d-455d-8228-7a990b75a0ee"
		};

		static constexpr BadgerBLE::CharacteristicDef SERVICE_ECHO_CHARACTERISTICS[] =
		{
			{
				.name = "badgeros.badge.bluetooth.services.echo.request",
				.uuid = "e57769c4-0a77-41cd-801f-b6815ac1f612",
				.attributes = NIMBLE_PROPERTY::WRITE
			},

			{
				.name = "badgeros.badge.bluetooth.services.echo.response",
				.uuid = "02a2963d-a08e-4d77-8bcc-d7413254246a",
				.attributes = NIMBLE_PROPERTY::READ
			}
		};

		static constexpr BadgerBLE::ServiceSpec SERVICESPEC_ECHO(SERVICE_ECHO, SERVICE_ECHO_CHARACTERISTICS);
	}
}
