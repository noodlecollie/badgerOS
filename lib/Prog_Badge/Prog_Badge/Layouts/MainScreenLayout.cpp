#include <Resources/Images/PlaceholderChar.h>
#include <Resources/Fonts/ArialStdFont.h>
#include <BadgerUI/FontData/ArialStdFontData.h>
#include "MainScreenLayout.h"
#include "../UIModule.h"
#include "../InputModule.h"
#include "../InputDefs.h"

namespace Badge
{
	// For a 128x128 screen, the character display area here is 128x94.
	static constexpr uint16_t STATUS_AREA_HEIGHT = 8;
	static constexpr uint16_t SEPARATOR_THICKNESS = 2;
	static constexpr uint16_t TEXT_AREA_HEIGHT = 24;

	MainScreenLayout::MainScreenLayout(uint16_t width, uint16_t height) :
		BadgerUI::FixedDimensionLayout(width, height)
	{
	}

	void MainScreenLayout::onSetup()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		m_StatusBarArea.setDrawStyle(ShapeDrawStyle::Filled);
		m_StatusBarArea.setFillColour(ColourProperty(ColourScheme::Colour_BackgroundAlt));
		m_StatusBarArea.setRect(UIRect(UIPoint(0, 0), layoutWidth(), STATUS_AREA_HEIGHT));
		addItemToTail(&m_StatusBarArea);

		m_MessageAreaSeparator.setDrawStyle(ShapeDrawStyle::Filled);
		m_MessageAreaSeparator.setFillColour(ColourProperty(ColourScheme::Colour_Secondary));
		m_MessageAreaSeparator.setRect(UIRect(UIPoint(0, layoutHeight() - TEXT_AREA_HEIGHT - SEPARATOR_THICKNESS), layoutWidth(), SEPARATOR_THICKNESS));
		addItemToTail(&m_MessageAreaSeparator);

		m_PlaceholderCharacterImage.setBitmap(&Resources::PlaceholderChar::BITMAP);
		m_PlaceholderCharacterImage.setPosition(UIPoint(0, STATUS_AREA_HEIGHT));
		m_PlaceholderCharacterImage.setOverrideDimensions(UIDimensions(layoutWidth(), m_MessageAreaSeparator.rect().min().y() - STATUS_AREA_HEIGHT));
		addItemToTail(&m_PlaceholderCharacterImage);

		m_MessageLabel.setRect(UIRect(UIPoint(0, layoutHeight() - TEXT_AREA_HEIGHT), layoutWidth(), TEXT_AREA_HEIGHT));
		m_MessageLabel.setHorizontalAlignment(BadgerUI::HAlignment::Centre);
		m_MessageLabel.setVerticalAlignment(BadgerUI::VAlignment::Centre);
		m_MessageLabel.setText("Testing");
		m_MessageLabel.setFont(&BadgerUI::ArialStdFontData::staticInstance().fontObject());
		m_MessageLabel.setFillColour(ColourProperty(ColourScheme::Colour_Background));
		m_MessageLabel.setDrawStyle(BadgerGL::ShapeDrawStyle::Filled);

		addItemToTail(&m_MessageLabel);
	}

	void MainScreenLayout::onPreUpdate(const BadgerUI::UIUpdateContext& context)
	{
		if ( context.buttons->wasPressedThisFrame(Input::ButtonMain) )
		{
			UIModule::setNextScreen(UIModuleResources::ScreenID::CharacterInfoScreen);
		}
	}
}
