#pragma once

#include <BadgerUI/BaseLayout.h>
#include <BadgerUI/Box.h>
#include <BadgerUI/Label.h>
#include <BadgerUI/FontDirectory.h>

namespace InkyImpressionSanityTest
{
	class TestCardLayout : public BadgerUI::BaseLayout
	{
	public:
		void init(const BadgerUI::FontDirectory& fontDir);

	private:
		BadgerUI::Box m_Border;
		BadgerUI::Box m_FilledOutlineBox;
		BadgerUI::Label m_Label;
	};
}
