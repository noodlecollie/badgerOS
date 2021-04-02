#include <cstring>
#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEUtils.h>
#include <NimBLEServer.h>
#include <Prog_Badge/Bluetooth/BadgeBLEServer.h>
#include <StringLib/StringUtils.h>
#include <PlatformConfig/Versions.h>
#include <BadgerBLE/ServiceSpec.h>

// Services:
#include <Prog_Badge/Bluetooth/Services/Echo.h>

namespace Badge
{
	static NimBLEService* createService(const BadgerBLE::ServiceSpec& spec)
	{
		BadgerBLE::ServiceDef serviceDef = spec.service();
		NimBLEService* service =  NimBLEDevice::getServer()->createService(serviceDef.uuid);

		if ( !service )
		{
			Serial.printf("Failed to create Bluetooth BLE service %s\r\n", serviceDef.name);
			return nullptr;
		}

		bool allCharacteristicsSuccessful = true;

		for ( size_t index = 0; index < spec.characteristicCount(); ++index )
		{
			if ( !service->createCharacteristic(spec[index].uuid, spec[index].attributes) )
			{
				Serial.printf("Failed to create characteristic %s for Bluetooth BLE service %s\r\n", spec[index].name, serviceDef.name);
				allCharacteristicsSuccessful = false;
			}
		}

		if ( allCharacteristicsSuccessful )
		{
			service->start();

			NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
			advertising->addServiceUUID(serviceDef.uuid);
		}

		return service;
	}

	BadgeBLEServer::BadgeBLEServer()
	{
		StringLib::snprintf_safe(m_Name, sizeof(m_Name), "Badge-%s", PlatformConfig::Versions::VERSION_BUILD_HASH_STRING);
	}

	void BadgeBLEServer::initialise()
	{
		NimBLEDevice::init(m_Name);

		NimBLEServer* server = NimBLEDevice::createServer();

		if ( !server )
		{
			Serial.printf("Failed to initialise Bluetooth BLE server!\r\n");
			return;
		}

		m_EchoService = createService(BluetoothServices::SERVICESPEC_ECHO);
	}

	void BadgeBLEServer::startAdvertising()
	{
		NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
		advertising->setScanResponse(true);
		advertising->setMinPreferred(0x12);

		NimBLEDevice::startAdvertising();
	}
}
