#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <CoreUtil/BgrsAssert.h>
#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/ColourScheme.h>
#include <Input/ButtonInputRecorder.h>

#include "InkyImpressionSanityTest.h"
#include "TestCardLayout.h"

namespace InkyImpressionSanityTest
{
	using BitmapSurface = BadgerGL::StaticPalettedBitmapSurface<InkyImpression::INKY_DISPLAY_WIDTH, 4>;

	static BitmapSurface LocalBitmapSurface;
	static BadgerGL::BitmapRenderer LocalBitmapRenderer(&LocalBitmapSurface);
	static BadgerUI::ColourScheme LocalColourScheme;
	static TestCardLayout LocalTestCardLayout;

	static uint8_t displayPixelCallback(uint32_t pixelIndex)
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		const uint32_t pixelIndexOnSurface = pixelIndex % BitmapSurface::PIXEL_COUNT;

		if ( pixelIndexOnSurface == 0 )
		{
			// Progressed to next segment - redraw.

			LocalBitmapSurface.fill(LocalColourScheme.colour(ColourScheme::Colour_Background));

			const int16_t baseRow = pixelIndex / InkyImpression::INKY_DISPLAY_WIDTH;
			LocalBitmapRenderer.setDrawingOffset(Point16(0, -baseRow));

			UIDrawContext drawContext;
			drawContext.screenBuffer = &LocalBitmapSurface;
			drawContext.renderer = &LocalBitmapRenderer;
			drawContext.colourScheme = &LocalColourScheme;

			LocalTestCardLayout.drawAllItems(drawContext);
		}

		return *(LocalBitmapSurface.constPixelData<uint8_t>() + pixelIndexOnSurface);
	}

	static void prepareTestImage()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		LocalColourScheme.setColour(ColourScheme::Colour_Background, InkyImpression::COL_WHITE);
		LocalColourScheme.setColour(ColourScheme::Colour_Primary, InkyImpression::COL_RED);
		LocalColourScheme.setColour(ColourScheme::Colour_Secondary, InkyImpression::COL_BLUE);

		UIUpdateContext updateContext;
		updateContext.currentTimeMs = millis();

		Input::ButtonInputRecorder buttonInput;
		updateContext.buttons = &buttonInput;

		LocalTestCardLayout.updateItems(updateContext);
	}

	void getPlatformConfigArgs(PlatformConfig::ConfigArgs& args)
	{
		static constexpr PlatformConfig::SPIConfig SPI_CONFIG =
		{
			.dataMode = SPI_MODE0,
			.bitOrder = MSBFIRST,
			.clockMode = PlatformConfig::SPIConfig::ClockRateMode::Frequency,
			.clockValue = 3000000
		};

		args.display = PlatformConfig::DisplayType::InkyImpression;
		args.userSPIConfig = &SPI_CONFIG;
	}

	void setup()
	{
		using namespace PlatformConfig;

		const PlatformConfigObject* configObject = globalConfig();

		configObject->initialiseSubsystem<PlatformConfigObject::SerialConfig>([](const SerialConfig& config)
		{
			Serial.begin(config.baudRate);
		});

		BGRS_ASSERT(configObject->args().display == PlatformConfig::DisplayType::InkyImpression, "Inky Impression display must be used.");

		const PlatformConfigObject::SPIConfig* spiConfig = configObject->getElement<PlatformConfigObject::SPIConfig>();
		const PlatformConfigObject::SPIPinConfig* spiPinConfig = configObject->getElement<PlatformConfigObject::SPIPinConfig>();
		const PlatformConfigObject::InkyImpressionConfig* inkyConfig = configObject->getElement<PlatformConfigObject::InkyImpressionConfig>();
		const PlatformConfigObject::SerialConfig* serialConfig = configObject->getElement<PlatformConfigObject::SerialConfig>();
		const PlatformConfigObject::ChipSelectConfig* chipSelectConfig = configObject->getElement<PlatformConfigObject::ChipSelectConfig>();

		Serial.printf("Sanity test initialising...\r\n");
		Serial.printf("Version %s\r\n", PlatformConfig::Versions::VERSION_STRING_FULL);
		Serial.printf("\r\n");

		Serial.printf("=== Chip select configuration ===\r\n");
		Serial.printf("           Display: %u\r\n", chipSelectConfig->displayCSPin);
		Serial.printf("\r\n");

		Serial.printf("=== Serial configuration ===\r\n");
		Serial.printf("         Baud rate: %u\r\n", serialConfig->baudRate);
		Serial.printf("\r\n");

		Serial.printf("=== InkyImpression configuration ===\r\n");
		Serial.printf("             Reset: %u\r\n", inkyConfig->resetPin);
		Serial.printf("      Data/command: %u\r\n", inkyConfig->dataCommandPin);
		Serial.printf("              Busy: %u\r\n", inkyConfig->busyPin);
		Serial.printf("\r\n");

		Serial.printf("=== SPI configuration ===\r\n");
		Serial.printf("         Data mode: %u\r\n", spiConfig->dataMode);
		Serial.printf("         Bit order: %u\r\n", spiConfig->bitOrder);
		Serial.printf("        Clock mode: %s\r\n", spiConfig->clockMode == PlatformConfig::SPIConfig::ClockRateMode::Divider ? "divider" : "frequency");
		Serial.printf("       Clock value: %u\r\n", spiConfig->clockValue);
		Serial.printf("         Clock pin: %u\r\n", spiPinConfig->clockPin);
		Serial.printf("          MISO pin: %u\r\n", spiPinConfig->misoPin);
		Serial.printf("          MOSI pin: %u\r\n", spiPinConfig->mosiPin);
		Serial.printf(" Write protect pin: %u\r\n", spiPinConfig->writeProtectPin);
		Serial.printf("          Hold pin: %u\r\n", spiPinConfig->holdPin);
		Serial.printf("\r\n");

		PlatformConfig::chipSelectSetup(*chipSelectConfig);
		PlatformConfig::spiSetup(*spiConfig);

		SPI.begin(spiPinConfig->clockPin,
				  spiPinConfig->misoPin,
				  spiPinConfig->mosiPin,
				  chipSelectConfig->displayCSPin);

		InkyImpression::Driver.initialise(*inkyConfig);

		prepareTestImage();
		InkyImpression::Driver.writeImagePixelwise(&displayPixelCallback);

		Serial.println("Sanity test initialised.");
	}

	void loop()
	{
	}
}
