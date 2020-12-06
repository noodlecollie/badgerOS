#pragma once

#include <BadgerUI/BaseLayout.h>
#include <BadgerUI/Box.h>
#include <BadgerUI/Bitmap.h>
#include <BadgerUI/UIDrawableAlias.h>

namespace SSD1351SanityTest
{
	class TestCardLayout : public BadgerUI::BaseLayout
	{
	public:
		TestCardLayout();

	private:
		BadgerUI::Box m_FilledBox;
		BadgerUI::Box m_OutlineBox;
		BadgerUI::Box m_FilledOutlineBox;
		BadgerUI::Bitmap m_TiledImage;
		BadgerUI::Box m_OuterBox;
		BadgerUI::UIDrawableAlias m_OuterBoxAliases[4];
	};
}
