#include <CoreUtil/TimeHelpers.h>
#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>
#include "Badge.h"
#include "UIModule.h"
#include "CommandModule.h"
#include "InputModule.h"

namespace Badge
{
	template<typename T, typename FUNC>
	static inline void initialiseSubsystem(const char* stage, const T* PlatformConfig::ConfigData::* configEntryPtr, const FUNC& initFunc)
	{
		Serial.printf("  * %s...", stage);
		const CoreUtil::TimevalMs startTime = millis();

		initialiseSubsystem(configEntryPtr, initFunc);

		const CoreUtil::TimevalMs duration = millis() - startTime;
		Serial.printf(" Done. (%.2fs)\r\n", static_cast<float>(duration) / 1000.0f);
	}

	template<typename FUNC>
	static inline void initialiseSubsystem(const char* stage, const FUNC& initFunc)
	{
		Serial.printf("  * %s...", stage);
		const CoreUtil::TimevalMs startTime = millis();

		initFunc(PlatformConfig::globalConfigData());

		const CoreUtil::TimevalMs duration = millis() - startTime;
		Serial.printf(" Done. (%.2fs)\r\n", static_cast<float>(duration) / 1000.0f);
	}

	static void initSubsystems()
	{
		using namespace PlatformConfig;

		initialiseSubsystem(&ConfigData::serialConfig, [](const SerialConfig& config)
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

		initialiseSubsystem("CommandModule", [](const ConfigData& config)
		{
			CommandModule::setup();
		});

		initialiseSubsystem("InputModule", [](const ConfigData& config)
		{
			InputModule::setup();
		});

		initialiseSubsystem("Power measurement", &ConfigData::powerConfig, &powerSetup);
		initialiseSubsystem("Chip select pins", &ConfigData::chipSelectConfig, &chipSelectSetup);
		initialiseSubsystem("SPI setup", &ConfigData::spiConfig, &spiSetup);

		initialiseSubsystem("SPI begin", [](const ConfigData& config)
		{
			// Ensure that these exist.
			globalConfigItem(&ConfigData::spiPinConfig);
			globalConfigItem(&ConfigData::chipSelectConfig);

			SPI.begin(config.spiPinConfig->clockPin, config.spiPinConfig->misoPin, config.spiPinConfig->mosiPin, config.chipSelectConfig->displayCSPin);
		});

		initialiseSubsystem("OLED", &ConfigData::ssd1351Config, [](const SSD1351::OLEDDriver::Config& config)
		{
			SSD1351::Driver.initialise(config);
		});

		initialiseSubsystem("UIModule", [](const ConfigData& config)
		{
			UIModule::setup();
		});

		const CoreUtil::TimevalMs initDuration = millis() - initStartTime;
		Serial.printf("Initialisation complete. (%.2fs)\r\n", static_cast<float>(initDuration) / 1000.0f);
	}

	void getPlatformConfigArgs(PlatformConfig::ConfigArgs& args)
	{
		args.display = PlatformConfig::DisplayType::SSD1351;
	}

	void setup()
	{
		initSubsystems();
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
		UIModule::loop(currentTime);

		lastUpdate = currentTime;
	}
}
