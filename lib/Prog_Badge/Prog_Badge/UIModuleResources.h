#pragma once

#include <SSD1351/Defs.h>
#include <SSD1351/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/BaseUIDrawable.h>
#include <BadgerUI/LayoutContainer.h>
#include <Input/ButtonInputRecorder.h>
#include "Layouts/MainScreenLayout.h"
#include "Layouts/CharacterInfoScreenLayout.h"

namespace Badge
{
	class UIModuleResources
	{
	public:
#define SCREEN_ID_LIST \
	LIST_ITEM(MainScreen = 0, "MainScreen") \
	LIST_ITEM(CharacterInfoScreen, "CharacterInfoScreen")

#define LIST_ITEM(value, name) value,
		enum ScreenID
		{
			SCREEN_ID_LIST

			ScreenCount,
			InvalidScreen = -1
		};
#undef LIST_ITEM

		static const char* screenName(ScreenID id);

		UIModuleResources();

		void setup();
		void loop(CoreUtil::TimevalMs currentTime);

		ScreenID currentScreen() const;
		void setNextScreen(ScreenID id);

	private:
		inline void setUpScreen(BadgerUI::BaseLayout& screen, ScreenID id)
		{
			screen.setup();
			m_LayoutContainer.mapIndexToLayout(id, &screen);
		}

		inline void sendScreenBuffer()
		{
			SSD1351::Driver.writeImage(CoreUtil::ConstBlob(m_ScreenBufferSurface.rawPixelData(), m_ScreenBufferSurface.pixelDataSize()));
		}

		bool updateUI(CoreUtil::TimevalMs currentTime);
		bool renderUI();

		// Resources
		BadgerGL::Static65KBitmapSurface<SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT> m_ScreenBufferSurface;
		BadgerUI::ColourScheme m_ColScheme;

		// Screen management
		BadgerUI::LayoutContainer<ScreenCount> m_LayoutContainer;
		ScreenID m_NextScreenID = ScreenID::MainScreen;

		// Screens
		MainScreenLayout m_MainScreen;
		CharacterInfoScreenLayout m_CharInfoScreen;
	};
}
