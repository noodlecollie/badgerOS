#include <CoreUtil/TimeHelpers.h>
#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>
#include "Badge.h"
#include <Prog_Badge/UIModule.h>
#include <Prog_Badge/CommandModule.h>
#include <Prog_Badge/InputModule.h>
#include <Prog_Badge/BluetoothModule.h>

namespace Badge
{
	template<typename T, typename FUNC>
	static inline void initialiseSubsystem(const char* stage, const FUNC& initFunc)
	{
		Serial.printf("  * %s...", stage);
		const CoreUtil::TimevalMs startTime = millis();

		PlatformConfig::globalConfig()->initialiseSubsystem<T>(initFunc);

		const CoreUtil::TimevalMs duration = millis() - startTime;
		Serial.printf(" Done. (%.2fs)\r\n", static_cast<float>(duration) / 1000.0f);
	}

	template<typename FUNC>
	static inline void initialiseSubsystem(const char* stage, const FUNC& initFunc)
	{
		Serial.printf("  * %s...", stage);
		const CoreUtil::TimevalMs startTime = millis();

		initFunc();

		const CoreUtil::TimevalMs duration = millis() - startTime;
		Serial.printf(" Done. (%.2fs)\r\n", static_cast<float>(duration) / 1000.0f);
	}

	void getPlatformConfigArgs(PlatformConfig::ConfigArgs& args)
	{
		args.display = PlatformConfig::DisplayType::SSD1351;
	}

	void setup()
	{
		using namespace PlatformConfig;
		const PlatformConfigObject* configObject = globalConfig();

		configObject->initialiseSubsystem<SerialConfig>([](const SerialConfig& config)
		{
			Serial.begin(config.baudRate);
			Serial.flush();
		});

		Serial.printf("\r\n");
		Serial.printf("====================================\r\n");
		Serial.printf("         BadgerOS booting...        \r\n");
		Serial.printf("====================================\r\n");
		Serial.printf("Version %s\r\n", Versions::VERSION_STRING_FULL);
		Serial.printf("Beginning initialisation.\r\n");

		const CoreUtil::TimevalMs initStartTime = millis();

		initialiseSubsystem("CommandModule", &CommandModule::setup);
		initialiseSubsystem("InputModule", &InputModule::setup);

		initialiseSubsystem<ChipSelectConfig>("Chip select pins", &chipSelectSetup);
		initialiseSubsystem<SPIConfig>("SPI setup",  &spiSetup);

		initialiseSubsystem("SPI begin", [configObject]()
		{
			const SPIPinConfig* spiPinConfig = configObject->getElement<SPIPinConfig>();
			const ChipSelectConfig* chipSelectConfig = configObject->getElement<ChipSelectConfig>();

			SPI.begin(spiPinConfig->clockPin, spiPinConfig->misoPin, spiPinConfig->mosiPin, chipSelectConfig->displayCSPin);
		});

		initialiseSubsystem<PlatformConfigObject::SSD1351Config>("OLED", [](const PlatformConfigObject::SSD1351Config& config)
		{
			SSD1351::Driver.initialise(config);
		});

		initialiseSubsystem("UIModule", &UIModule::setup);
		initialiseSubsystem("BluetoothModule", &BluetoothModule::setup);

		const CoreUtil::TimevalMs initDuration = millis() - initStartTime;
		Serial.printf("Initialisation complete. (%.2fs)\r\n", static_cast<float>(initDuration) / 1000.0f);
	}

	void loop()
	{
		static constexpr CoreUtil::TimevalMs UPDATE_INTERVAL_MS = 100;
		static CoreUtil::TimevalMs lastUpdate = 0;

		const CoreUtil::TimevalMs currentTime = millis();

		if ( currentTime - lastUpdate < UPDATE_INTERVAL_MS )
		{
			return;
		}

		InputModule::loop();
		CommandModule::loop();
		BluetoothModule::loop();
		UIModule::loop(currentTime);

		lastUpdate = currentTime;
	}
}
