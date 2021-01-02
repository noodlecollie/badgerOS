#include <BadgerUI/Fonts/ArialStdFont.h>
#include <InkyImpression/Defs.h>
#include "TestCardLayout.h"

namespace InkyImpressionSanityTest
{
	TestCardLayout::TestCardLayout() :
		BadgerUI::BaseLayout()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		m_Border.setRect(UIRect(UIPoint(0, 0), InkyImpression::INKY_DISPLAY_WIDTH, InkyImpression::INKY_DISPLAY_HEIGHT));
		m_Border.setDrawStyle(ShapeDrawStyle::Outline);
		m_Border.setOutlineColour(ColourProperty(ColourScheme::Colour_Primary));
		m_Border.setOutlineWidth(5);
		addItemToTail(&m_Border);

		m_FilledOutlineBox.setRect(UIRect(UIPoint(30, 30), InkyImpression::INKY_DISPLAY_WIDTH - 60, InkyImpression::INKY_DISPLAY_HEIGHT - 60));
		m_FilledOutlineBox.setDrawStyle(ShapeDrawStyle::FilledOutline);
		m_FilledOutlineBox.setOutlineColour(ColourProperty(ColourScheme::Colour_Primary));
		m_FilledOutlineBox.setFillColour(ColourProperty(ColourScheme::Colour_Secondary));
		m_FilledOutlineBox.setOutlineWidth(2);
		addItemToTail(&m_FilledOutlineBox);

		m_Label.setFont(&Fonts::ArialStd);
		m_Label.setRect(UIRect(UIPoint(150, 204), 300, 40));
		m_Label.setFillColour(ColourProperty(ColourScheme::Colour_Background));
		m_Label.setDrawStyle(BadgerGL::ShapeDrawStyle::Filled);
		m_Label.setTextColour(ColourProperty(ColourScheme::Colour_Custom, InkyImpression::COL_BLACK));
		m_Label.setHorizontalAlignment(HAlignment::Centre);
		m_Label.setVerticalAlignment(VAlignment::Centre);
		m_Label.setText("Good riddance, 2020!");
		addItemToTail(&m_Label);
	}
}
