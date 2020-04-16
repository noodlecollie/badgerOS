#pragma once

#include <BadgerUI/BaseLayout.h>
#include <BadgerUI/Box.h>
#include <BadgerUI/Image.h>

namespace SanityTest
{
	class TestCardLayout : public BadgerUI::BaseLayout
	{
	public:
		TestCardLayout();

	private:
		BadgerUI::Box m_FilledBox;
		BadgerUI::Box m_OutlineBox;
		BadgerUI::Box m_FilledOutlineBox;
		BadgerUI::Image m_TiledImage;
		BadgerUI::Box m_OuterBoxes[4];
	};
}
