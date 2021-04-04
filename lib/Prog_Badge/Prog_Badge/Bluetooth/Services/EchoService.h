#pragma once

#include <Prog_Badge/Bluetooth/Services/IBadgeBLEService.h>
#include <NimBLEService.h>
#include <NimBLECharacteristic.h>

namespace Badge
{
	namespace BLEServices
	{
		class EchoService : public IBadgeBLEService, private NimBLECharacteristicCallbacks
		{
		public:
			virtual ~EchoService() = default;

			NimBLEService* initialise(NimBLEServer& server) override;
			void loop(NimBLEServer& server) override;

		private:
			void onRead(NimBLECharacteristic* pCharacteristic) override;
			void onRead(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc) override;
			void onWrite(NimBLECharacteristic* pCharacteristic) override;
			void onWrite(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc) override;
			void onNotify(NimBLECharacteristic* pCharacteristic) override;
			void onStatus(NimBLECharacteristic* pCharacteristic, Status s, int code) override;
			void onSubscribe(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc, uint16_t subValue) override;

			bool m_Valid = false;
			NimBLEService* m_Service = nullptr;
			NimBLECharacteristic* m_Request = nullptr;
			NimBLECharacteristic* m_Response = nullptr;
			bool m_RequestChanged = false;
		};
	}
}
