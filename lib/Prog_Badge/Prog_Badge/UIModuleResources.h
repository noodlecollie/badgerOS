#pragma once

#include <SSD1351/Defs.h>
#include <SSD1351/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/BaseUIDrawable.h>
#include <Input/ButtonInputRecorder.h>
#include "Layouts/MainScreenLayout.h"
#include "Layouts/CharacterInfoScreenLayout.h"

namespace Badge
{
	class UIModuleResources
	{
	public:
		enum ScreenID
		{
			MainScreen = 0,
			CharacterInfoScreen,

			ScreenCount,
			InvalidScreen = -1
		};

		UIModuleResources();

		void setup();
		void loop(CoreUtil::TimevalMs currentTime);

		ScreenID currentScreen() const;
		void setCurrentScreen(ScreenID id);

		BadgerGL::Static65KBitmapSurface<SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT> screenBufferSurface;
		BadgerUI::ColourScheme colScheme;
		BadgerUI::FontDirectory fontDirectory;

		// Screens
		MainScreenLayout mainScreen;
		CharacterInfoScreenLayout charInfoScreen;

	private:
		inline void setUpScreen(BadgerUI::BaseLayout& screen, ScreenID id)
		{
			screen.setup();
			m_Screens[id] = &screen;
		}

		inline void sendScreenBuffer()
		{
			SSD1351::Driver.writeImage(CoreUtil::ConstBlob(screenBufferSurface.rawPixelData(), screenBufferSurface.pixelDataSize()));
		}

		bool updateUI(BadgerUI::BaseLayout& screen, CoreUtil::TimevalMs currentTime);
		bool renderUI(BadgerUI::BaseLayout& screen);

		ScreenID m_CurrentScreen = InvalidScreen;
		BadgerUI::BaseLayout* m_Screens[ScreenCount];
	};
}
