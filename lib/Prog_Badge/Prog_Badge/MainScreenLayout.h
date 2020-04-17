#pragma once

#include <BadgerUI/BaseLayout.h>
#include <BadgerUI/Box.h>
#include <BadgerUI/Image.h>

namespace Badge
{
	class MainScreenLayout : public BadgerUI::BaseLayout
	{
	public:
		MainScreenLayout(uint16_t width, uint16_t height);

	private:
		uint16_t m_Width = 0;
		uint16_t m_Height = 0;

		BadgerUI::Box m_StatusBarArea;
		BadgerUI::Box m_MessageAreaSeparator;

		// Placeholders - to be replaced once we have the correct things up and running.
		BadgerUI::Image m_PlaceholderCharacterImage;
		BadgerUI::Box m_PlaceholderScrollingText;
	};
}
