#pragma once

#include <BadgerUI/FixedDimensionLayout.h>
#include <BadgerUI/Box.h>
#include <BadgerUI/Bitmap.h>
#include <BadgerUI/MaskedBitmap.h>
#include <BadgerUI/Label.h>

namespace Badge
{
	class MainScreenLayout : public BadgerUI::FixedDimensionLayout
	{
	public:
		MainScreenLayout(uint16_t width, uint16_t height);

		void SetMessage(const char* message);

	protected:
		virtual void onSetup() override;
		virtual void onPreUpdate(const BadgerUI::UIUpdateContext& context) override;

	private:
		BadgerUI::Box m_StatusBarArea;
		BadgerUI::Box m_MessageAreaSeparator;
		BadgerUI::Label m_MessageLabel;

		// Placeholders - to be replaced once we have the correct things up and running.
		BadgerUI::Bitmap m_PlaceholderCharacterImage;

		char m_Message[32];
	};
}
