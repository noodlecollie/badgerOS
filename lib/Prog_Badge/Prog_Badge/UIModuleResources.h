#pragma once

#include <SSD1351/Defs.h>
#include <SSD1351/OLEDDriver.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerUI/BaseUIDrawable.h>
#include <Input/ButtonInputRecorder.h>
#include "MainScreenLayout.h"

namespace Badge
{
	struct UIModuleResources
	{
		UIModuleResources();

		void setup();
		void loop(CoreUtil::TimevalMs currentTime);

		BadgerGL::Static65KBitmapSurface<SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT> screenBufferSurface;
		MainScreenLayout mainScreen;
		BadgerUI::ColourScheme colScheme;
		BadgerUI::FontDirectory fontDirectory;

	private:
		bool updateUI(CoreUtil::TimevalMs currentTime);
		void renderUI();
	};
}
