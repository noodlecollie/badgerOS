#include <CoreUtil/ArrayUtil.h>
#include <Resources/Images/Missing.h>
#include <InkyImpression/Defs.h>
#include "TestCardLayout.h"

namespace InkyImpressionSanityTest
{
	TestCardLayout::TestCardLayout() :
		BadgerUI::BaseLayout()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		m_Border.setRect(UIRect(UIPoint(0, 0), InkyImpression::DISPLAY_WIDTH, InkyImpression::DISPLAY_HEIGHT));
		m_Border.setDrawStyle(ShapeDrawStyle::Outline);
		m_Border.setOutlineColour(ColourProperty(ColourScheme::Colour_Primary));
		m_Border.setOutlineWidth(5);
		addItemToTail(&m_Border);

		m_FilledOutlineBox.setRect(UIRect(UIPoint(30, 30), InkyImpression::DISPLAY_WIDTH - 60, InkyImpression::DISPLAY_HEIGHT - 60));
		m_FilledOutlineBox.setDrawStyle(ShapeDrawStyle::FilledOutline);
		m_FilledOutlineBox.setOutlineColour(ColourProperty(ColourScheme::Colour_Primary));
		m_FilledOutlineBox.setFillColour(ColourProperty(ColourScheme::Colour_Secondary));
		m_FilledOutlineBox.setOutlineWidth(2);
		addItemToTail(&m_FilledOutlineBox);
	}
}
