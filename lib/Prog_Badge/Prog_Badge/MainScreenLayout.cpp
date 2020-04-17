#include <Resources/Images/Missing.h>
#include "MainScreenLayout.h"

namespace Badge
{
	static constexpr uint16_t STATUS_AREA_HEIGHT = 8;
	static constexpr uint16_t SEPARATOR_THICKNESS = 2;
	static constexpr uint16_t TEXT_AREA_HEIGHT = 24;

	MainScreenLayout::MainScreenLayout(uint16_t width, uint16_t height) :
		BadgerUI::BaseLayout(),
		m_Width(width),
		m_Height(height)
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		m_StatusBarArea.setDrawStyle(ShapeDrawStyle::Filled);
		m_StatusBarArea.setFillColour(ColourProperty(ColourScheme::Colour_BackgroundAlt));
		m_StatusBarArea.setRect(UIRect(UIPoint(0, 0), m_Width, STATUS_AREA_HEIGHT));
		addItemToTail(&m_StatusBarArea);

		m_MessageAreaSeparator.setDrawStyle(ShapeDrawStyle::Filled);
		m_MessageAreaSeparator.setFillColour(ColourProperty(ColourScheme::Colour_Secondary));
		m_MessageAreaSeparator.setRect(UIRect(UIPoint(0, height - TEXT_AREA_HEIGHT - SEPARATOR_THICKNESS), m_Width, SEPARATOR_THICKNESS));
		addItemToTail(&m_MessageAreaSeparator);

		m_PlaceholderCharacterImage.setBitmap(&Resources::Missing::BITMAP);
		m_PlaceholderCharacterImage.setPosition(UIPoint(0, STATUS_AREA_HEIGHT));
		m_PlaceholderCharacterImage.setOverrideDimensions(UIDimensions(m_Width, m_MessageAreaSeparator.rect().min().y() - STATUS_AREA_HEIGHT));
		addItemToTail(&m_PlaceholderCharacterImage);

		m_PlaceholderScrollingText.setRect(UIRect(UIPoint(0, m_MessageAreaSeparator.rect().max().y()), m_Width, m_Height - m_MessageAreaSeparator.rect().max().y()));
		m_PlaceholderScrollingText.setDrawStyle(ShapeDrawStyle::Filled);
		m_PlaceholderScrollingText.setFillColour(ColourProperty(ColourScheme::Colour_Primary));
		addItemToTail(&m_PlaceholderScrollingText);
	}
}
