#pragma once

#include <BadgerUI/BaseLayout.h>
#include <BadgerUI/Box.h>
#include <BadgerUI/Bitmap.h>
#include <BadgerUI/MaskedBitmap.h>
#include <BadgerUI/Label.h>

namespace Badge
{
	class MainScreenLayout : public BadgerUI::BaseLayout
	{
	public:
		MainScreenLayout(uint16_t width, uint16_t height);

		virtual void setup() override;

	private:
		uint16_t m_Width = 0;
		uint16_t m_Height = 0;

		BadgerUI::Box m_StatusBarArea;
		BadgerUI::Box m_MessageAreaSeparator;
		BadgerUI::Label m_MessageLabel;

		// Placeholders - to be replaced once we have the correct things up and running.
		BadgerUI::Bitmap m_PlaceholderCharacterImage;
	};
}
