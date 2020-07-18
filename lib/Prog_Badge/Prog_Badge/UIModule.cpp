#include <Arduino.h>
#include <SSD1351/Defs.h>
#include <SSD1351/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/BaseUIDrawable.h>
#include "UIModule.h"
#include "MainScreenLayout.h"

namespace Badge
{
	namespace UIModule
	{
		static constexpr CoreUtil::TimevalMs UPDATE_INTERVAL_MS = 100;

		static BadgerGL::Static65KBitmapSurface<SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT> ScreenBufferSurface;
		static MainScreenLayout MainScreen(SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT);
		static BadgerUI::ColourScheme ColScheme;
		static CoreUtil::TimevalMs LastUpdate = 0;
		static BadgerUI::FontDirectory FontDirectory;

		const BadgerUI::FontDirectory& fontDirectory()
		{
			return FontDirectory;
		}

		void setup()
		{
			using namespace BadgerGL;
			using namespace BadgerUI;

			ColScheme.setColour(ColourScheme::Colour_Background, col24To16(0x000000));
			ColScheme.setColour(ColourScheme::Colour_BackgroundAlt, col24To16(0x534b62));
			ColScheme.setColour(ColourScheme::Colour_Primary, col24To16(0xfdfffc));
			ColScheme.setColour(ColourScheme::Colour_Secondary, col24To16(0xc0bcb5));

			FontDirectory.loadAllFonts();
			MainScreen.setup();
		}

		void loop()
		{
			using namespace BadgerGL;
			using namespace BadgerUI;

			const CoreUtil::TimevalMs currentTime = millis();

			if ( currentTime - LastUpdate < UPDATE_INTERVAL_MS )
			{
				return;
			}

			UIUpdateContext updateContext;
			updateContext.currentTimeMs = currentTime;

			MainScreen.updateItems(updateContext);
			LastUpdate = currentTime;

			if ( MainScreen.dirtyState() == DrawableDirtyState::NotDirty )
			{
				return;
			}

			BitmapRenderer renderer(&ScreenBufferSurface);

			UIDrawContext drawContext;
			drawContext.colourScheme = &ColScheme;
			drawContext.renderer = &renderer;
			drawContext.screenBuffer = &ScreenBufferSurface;
			drawContext.fontDirectory = &FontDirectory;

			switch ( MainScreen.dirtyState() )
			{
				case DrawableDirtyState::ContainerDirty:
				{
					MainScreen.drawAllItems(drawContext);
					break;
				}

				case DrawableDirtyState::ItemDirty:
				{
					MainScreen.drawDirtyItems(drawContext);
					break;
				}

				default:
				{
					break;
				}
			}

			if ( renderer.dirtyArea().isNull() )
			{
				return;
			}

			// For now, just send the whole screen buffer if anything is dirty.
			// This requires less overhead than converting the dirty area into consecutive bytes.
			SSD1351::Driver.writeImage(CoreUtil::ConstBlob(ScreenBufferSurface.rawPixelData(), ScreenBufferSurface.pixelDataSize()));
		}
	}
}
