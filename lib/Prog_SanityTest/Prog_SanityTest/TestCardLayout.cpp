#include <CoreUtil/ArrayUtil.h>
#include <Resources/Images/Missing.h>
#include "TestCardLayout.h"

namespace SanityTest
{
	TestCardLayout::TestCardLayout() :
		BadgerUI::BaseLayout()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		m_FilledBox.setRect(UIRect(UIPoint(8, 8), 32, 32));
		m_FilledBox.setDrawStyle(ShapeDrawStyle::Filled);
		m_FilledBox.setFillColour(ColourProperty(ColourScheme::Colour_Primary));
		addItemToTail(&m_FilledBox);

		m_OutlineBox.setRect(UIRect(UIPoint(48, 8), 32, 32));
		m_OutlineBox.setDrawStyle(ShapeDrawStyle::Outline);
		m_OutlineBox.setOutlineColour(ColourProperty(ColourScheme::Colour_Primary));
		m_OutlineBox.setOutlineWidth(4);
		addItemToTail(&m_OutlineBox);

		m_FilledOutlineBox.setRect(UIRect(UIPoint(88, 8), 32, 32));
		m_FilledOutlineBox.setDrawStyle(ShapeDrawStyle::FilledOutline);
		m_FilledOutlineBox.setOutlineColour(ColourProperty(ColourScheme::Colour_Primary));
		m_FilledOutlineBox.setFillColour(ColourProperty(ColourScheme::Colour_Secondary));
		m_FilledOutlineBox.setOutlineWidth(2);
		addItemToTail(&m_FilledOutlineBox);

		m_TiledImage.setBitmap(&Resources::Missing::BITMAP);
		m_TiledImage.setPosition(UIPoint(52, 12));
		m_TiledImage.setDimensions(UIDimensions(24, 24));
		addItemToTail(&m_TiledImage);

		for ( uint32_t index = 0; index < CoreUtil::arraySize(m_OuterBoxes); ++index )
		{
			BadgerUI::Box& box = m_OuterBoxes[index];

			box.setOutlineWidth(1);
			box.setOutlineColour(ColourProperty(ColourScheme::Colour_Custom, col24To16(0x000000)));
			box.setFillColour(ColourProperty(ColourScheme::Colour_Custom, col24To16(0xFFFFFF)));
			box.setDrawStyle(ShapeDrawStyle::FilledOutline);

			int16_t x = 0;
			int16_t y = 0;

			if ( index >= 2 )
			{
				y = 124;
			}

			if ( index % 2 )
			{
				x = 124;
			}

			box.setRect(UIRect(UIPoint(x, y), 4, 4));
			addItemToTail(&box);
		}
	}
}
