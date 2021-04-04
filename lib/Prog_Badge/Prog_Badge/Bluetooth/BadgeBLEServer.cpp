#include <cstring>
#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEUtils.h>
#include <NimBLEServer.h>
#include <Prog_Badge/Bluetooth/BadgeBLEServer.h>
#include <StringLib/StringUtils.h>
#include <PlatformConfig/Versions.h>

namespace Badge
{
	BadgeBLEServer::BadgeBLEServer()
	{
		// Default name:
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

		setUpService(m_EchoService.initialise(*server));
	}

	void BadgeBLEServer::loop()
	{
		NimBLEServer* server = NimBLEDevice::getServer();

		if ( !server )
		{
			return;
		}

		m_EchoService.loop(*server);
	}

	bool BadgeBLEServer::isAdvertisingEnabled() const
	{
		NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
		return advertising && advertising->isAdvertising();
	}

	void BadgeBLEServer::setAdvertisingEnabled(bool enabled)
	{
		if ( isAdvertisingEnabled() == enabled )
		{
			return;
		}

		NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();

		if ( !advertising )
		{
			return;
		}

		if ( enabled )
		{
			advertising->setScanResponse(true);
			advertising->setMinPreferred(0x12);
			advertising->start();
		}
		else
		{
			advertising->stop();
		}
	}

	void BadgeBLEServer::setUpService(NimBLEService* service)
	{
		if ( !service )
		{
			return;
		}

		service->start();

		NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
		advertising->addServiceUUID(service->getUUID());
	}
}
