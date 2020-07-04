#include <Resources/Images/Missing.h>
#include <Resources/Images/ChequerboardMask.h>
#include <Resources/Images/PlaceholderChar.h>
#include "MainScreenLayout.h"

namespace Badge
{
	// For a 128x128 screen, the character display area here is 128x94.
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
		m_MessageAreaSeparator.setRect(UIRect(UIPoint(0, m_Height - TEXT_AREA_HEIGHT - SEPARATOR_THICKNESS), m_Width, SEPARATOR_THICKNESS));
		addItemToTail(&m_MessageAreaSeparator);

		m_PlaceholderCharacterImage.setBitmap(&Resources::PlaceholderChar::BITMAP);
		m_PlaceholderCharacterImage.setPosition(UIPoint(0, STATUS_AREA_HEIGHT));
		m_PlaceholderCharacterImage.setOverrideDimensions(UIDimensions(m_Width, m_MessageAreaSeparator.rect().min().y() - STATUS_AREA_HEIGHT));
		addItemToTail(&m_PlaceholderCharacterImage);

		m_PlaceholderScrollingText.setBitmap(&Resources::ChequerboardMask::BITMAP);
		m_PlaceholderScrollingText.setPosition(UIPoint(0, m_Height -  TEXT_AREA_HEIGHT));
		m_PlaceholderScrollingText.setOverrideDimensions(UIDimensions(m_Width, TEXT_AREA_HEIGHT));
		m_PlaceholderScrollingText.setPrimaryColour(ColourProperty(ColourScheme::Colour_Custom, col24To16(0x0000FF)));
		addItemToTail(&m_PlaceholderScrollingText);
	}
}
