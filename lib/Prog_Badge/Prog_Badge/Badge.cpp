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
	static inline void initialiseSubsystem(const char* stage, const T* PlatformConfig::Config::* configEntryPtr, const FUNC& initFunc)
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

		initFunc(PlatformConfig::globalConfig());

		const CoreUtil::TimevalMs duration = millis() - startTime;
		Serial.printf(" Done. (%.2fs)\r\n", static_cast<float>(duration) / 1000.0f);
	}

	static void initSubsystems()
	{
		using namespace PlatformConfig;

		initialiseSubsystem(&Config::serialConfig, [](const SerialConfig& config)
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

		initialiseSubsystem("CommandModule", [](const Config& config)
		{
			CommandModule::setup();
		});

		initialiseSubsystem("InputModule", [](const Config& config)
		{
			InputModule::setup();
		});

		initialiseSubsystem("Power measurement", &Config::powerConfig, &powerSetup);
		initialiseSubsystem("Chip select pins", &Config::chipSelectConfig, &chipSelectSetup);
		initialiseSubsystem("SPI setup", &Config::spiConfig, &spiSetup);

		initialiseSubsystem("SPI begin", [](const Config& config)
		{
			// Ensure that these exist.
			globalConfigItem(&Config::spiPinConfig);
			globalConfigItem(&Config::chipSelectConfig);

			SPI.begin(config.spiPinConfig->clockPin, config.spiPinConfig->misoPin, config.spiPinConfig->mosiPin, config.chipSelectConfig->oledScreenCSPin);
		});

		initialiseSubsystem("OLED", &Config::ssd1351Config, [](const SSD1351::OLEDDriver::Config& config)
		{
			SSD1351::Driver.initialise(config);
		});

		initialiseSubsystem("UIModule", [](const Config& config)
		{
			UIModule::setup();
		});

		const CoreUtil::TimevalMs initDuration = millis() - initStartTime;
		Serial.printf("Initialisation complete. (%.2fs)\r\n", static_cast<float>(initDuration) / 1000.0f);
	}

	void setup()
	{
		initSubsystems();
	}

	void loop()
	{
		InputModule::loop();
		CommandModule::loop();
		UIModule::loop();
	}
}
