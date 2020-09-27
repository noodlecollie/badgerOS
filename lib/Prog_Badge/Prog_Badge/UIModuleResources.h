#pragma once

#include <SSD1351/Defs.h>
#include <SSD1351/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/BaseUIDrawable.h>
#include <BadgerUI/LayoutContainer.h>
#include <BadgerUI/FontDirectory.h>
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

		const BadgerGL::BitmapMaskFont* getFont(BadgerUI::FontID id) const;

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

		BadgerGL::Static65KBitmapSurface<SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT> m_ScreenBufferSurface;
		BadgerUI::LayoutContainer<ScreenCount> m_LayoutContainer;
		BadgerUI::ColourScheme m_ColScheme;
		BadgerUI::FontDirectory m_FontDirectory;

		// Screens
		MainScreenLayout m_MainScreen;
		CharacterInfoScreenLayout m_CharInfoScreen;
	};
}
