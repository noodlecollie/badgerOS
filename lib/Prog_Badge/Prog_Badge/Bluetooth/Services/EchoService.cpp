#include <Prog_Badge/Bluetooth/Services/EchoService.h>
#include <BadgerBLE/GATTDefs.h>
#include <NimBLEDescriptor.h>
#include <NimBLEServer.h>
#include <Arduino.h>
#include "Prog_Badge/UIModule.h"
#include "Prog_Badge/UIModuleResources.h"

namespace Badge
{
	namespace BLEServices
	{
		static constexpr BadgerBLE::ServiceDef SERVICE =
		{
			.name = "badgeros.badge.bluetooth.services.echo",
			.uuid = "cd7c6eeb-c20d-455d-8228-7a990b75a0ee"
		};

		static constexpr BadgerBLE::CharacteristicDef CH_REQUEST =
		{
			.name = "badgeros.badge.bluetooth.services.echo.request",
			.uuid = "e57769c4-0a77-41cd-801f-b6815ac1f612",
			.attributes = NIMBLE_PROPERTY::WRITE
		};

		static constexpr BadgerBLE::CharacteristicDef CH_RESPONSE =
		{
			.name = "badgeros.badge.bluetooth.services.echo.response",
			.uuid = "02a2963d-a08e-4d77-8bcc-d7413254246a",
			.attributes = NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
		};

		NimBLEService* EchoService::initialise(NimBLEServer& server)
		{
			m_Valid = false;
			m_Service = server.createService(SERVICE.uuid);

			if ( !m_Service )
			{
				Serial.printf("Failed to create Bluetooth BLE service %s\r\n", SERVICE.name);
				return nullptr;
			}

			m_Request = m_Service->createCharacteristic(CH_REQUEST.uuid, CH_REQUEST.attributes);

			if ( !m_Request )
			{
				Serial.printf("Failed to create characteristic %s for Bluetooth BLE service %s\r\n", CH_REQUEST.name, SERVICE.name);
			}

			m_Request->setCallbacks(this);

			m_Response = m_Service->createCharacteristic(CH_RESPONSE.uuid, CH_RESPONSE.attributes);

			if ( !m_Response )
			{
				Serial.printf("Failed to create characteristic %s for Bluetooth BLE service %s\r\n", CH_RESPONSE.name, SERVICE.name);
			}

			m_Valid = true;
			return m_Service;
		}

		void EchoService::loop(NimBLEServer& server)
		{
			if ( !m_Valid || !m_RequestChanged )
			{
				return;
			}

			Serial.printf("Setting %s value to \"%s\"\r\n", CH_RESPONSE.name, m_Request->getValue().c_str());

			m_RequestChanged = false;
			m_Response->setValue(m_Request->getValue());
			m_Response->notify();
		}

		void EchoService::onRead(NimBLECharacteristic* pCharacteristic)
		{
			// Empty override
		}

		void EchoService::onRead(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc)
		{
			// Empty override
		}

		void EchoService::onWrite(NimBLECharacteristic* pCharacteristic)
		{
			m_RequestChanged = true;
		}

		void EchoService::onWrite(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc)
		{
			// Empty override
		}

		void EchoService::onNotify(NimBLECharacteristic* pCharacteristic)
		{
			// Empty override
		}

		void EchoService::onStatus(NimBLECharacteristic* pCharacteristic, Status s, int code)
		{
			// Empty override
		}

		void EchoService::onSubscribe(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc, uint16_t subValue)
		{
			// Empty override
		}
	}
}
