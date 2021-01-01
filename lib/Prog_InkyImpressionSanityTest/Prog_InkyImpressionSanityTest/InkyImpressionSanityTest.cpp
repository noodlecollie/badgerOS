#include <SPI.h>
#include <Wire.h>
#include <Esp.h>
#include <CoreUtil/BgrsAssert.h>
#include <PlatformConfig/Platform.h>
#include <PlatformConfig/Versions.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/ColourScheme.h>
#include <BadgerUI/FontDirectory.h>
#include <Input/ButtonInputRecorder.h>

#include "InkyImpressionSanityTest.h"
#include "TestCardLayout.h"

namespace InkyImpressionSanityTest
{
	using BitmapSurface = BadgerGL::StaticPalettedBitmapSurface<InkyImpression::DISPLAY_WIDTH, 4>;

	static BitmapSurface LocalBitmapSurface;
	static BadgerGL::BitmapRenderer LocalBitmapRenderer(&LocalBitmapSurface);
	static BadgerUI::ColourScheme LocalColourScheme;
	static TestCardLayout LocalTestCardLayout;
	static BadgerUI::FontDirectory LocalFontDirectory;

	static uint8_t displayPixelCallback(uint32_t pixelIndex)
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		const uint32_t pixelIndexOnSurface = pixelIndex % BitmapSurface::PIXEL_COUNT;

		if ( pixelIndexOnSurface == 0 )
		{
			// Progressed to next segment - redraw.

			LocalBitmapSurface.fill(LocalColourScheme.colour(ColourScheme::Colour_Background));

			const int16_t baseRow = pixelIndex / InkyImpression::DISPLAY_WIDTH;
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

		LocalFontDirectory.loadAllFonts();

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
		const PlatformConfig::ConfigInstance& configInstance = PlatformConfig::globalConfig();
		const PlatformConfig::ConfigArgs& configArgs = configInstance.args();
		const PlatformConfig::ConfigData& configData = configInstance.data();

		BGRS_ASSERT(configData.serialConfig, "Serial config is required.");
		Serial.begin(configData.serialConfig->baudRate);

		BGRS_ASSERT(configArgs.display == PlatformConfig::DisplayType::InkyImpression, "Inky Impression display must be used.");
		BGRS_ASSERT(configInstance.inkyImpressionConfig(), "Inky Impression config is required.");
		BGRS_ASSERT(configData.spiConfig, "SPI config is required.");
		BGRS_ASSERT(configData.spiPinConfig, "SPI pin config is required.");
		BGRS_ASSERT(configData.chipSelectConfig, "Chip select config is required.");

		Serial.printf("Sanity test initialising...\r\n");
		Serial.printf("Version %s\r\n", PlatformConfig::Versions::VERSION_STRING_FULL);
		Serial.printf("\r\n");

		Serial.printf("=== Chip select configuration ===\r\n");
		Serial.printf("           Display: %u\r\n", configData.chipSelectConfig->displayCSPin);
		Serial.printf("\r\n");

		Serial.printf("=== Serial configuration ===\r\n");
		Serial.printf("         Baud rate: %u\r\n", configData.serialConfig->baudRate);
		Serial.printf("\r\n");

		Serial.printf("=== InkyImpression configuration ===\r\n");
		Serial.printf("             Reset: %u\r\n", configInstance.inkyImpressionConfig()->resetPin);
		Serial.printf("      Data/command: %u\r\n", configInstance.inkyImpressionConfig()->dataCommandPin);
		Serial.printf("              Busy: %u\r\n", configInstance.inkyImpressionConfig()->busyPin);
		Serial.printf("\r\n");

		Serial.printf("=== SPI configuration ===\r\n");
		Serial.printf("         Data mode: %u\r\n", configData.spiConfig->dataMode);
		Serial.printf("         Bit order: %u\r\n", configData.spiConfig->bitOrder);
		Serial.printf("        Clock mode: %s\r\n", configData.spiConfig->clockMode == PlatformConfig::SPIConfig::ClockRateMode::Divider ? "divider" : "frequency");
		Serial.printf("       Clock value: %u\r\n", configData.spiConfig->clockValue);
		Serial.printf("         Clock pin: %u\r\n", configData.spiPinConfig->clockPin);
		Serial.printf("          MISO pin: %u\r\n", configData.spiPinConfig->misoPin);
		Serial.printf("          MOSI pin: %u\r\n", configData.spiPinConfig->mosiPin);
		Serial.printf(" Write protect pin: %u\r\n", configData.spiPinConfig->writeProtectPin);
		Serial.printf("          Hold pin: %u\r\n", configData.spiPinConfig->holdPin);
		Serial.printf("\r\n");

		PlatformConfig::chipSelectSetup(*configData.chipSelectConfig);
		PlatformConfig::spiSetup(*configData.spiConfig);

		SPI.begin(configData.spiPinConfig->clockPin,
				  configData.spiPinConfig->misoPin,
				  configData.spiPinConfig->mosiPin,
				  configData.chipSelectConfig->displayCSPin);

		InkyImpression::Driver.initialise(*configInstance.inkyImpressionConfig());

		prepareTestImage();
		InkyImpression::Driver.writeImagePixelwise(&displayPixelCallback);

		Serial.println("Sanity test initialised.");
	}

	void loop()
	{
	}
}
