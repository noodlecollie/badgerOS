#include <Arduino.h>
#include <Resources/Fonts/ArialStdFont.h>
#include <BadgerUI/FontDirectory.h>
#include <BadgerUI/ColourScheme.h>
#include "CharacterInfoScreenLayout.h"
#include "../UIModule.h"
#include "../InputModule.h"
#include "../InputDefs.h"

namespace Badge
{
	static constexpr uint16_t PADDING = 5;
	static constexpr uint16_t KEY_VALUE_SPACING = 2;
	static constexpr uint16_t ROW_HEIGHT = 24;

	static constexpr size_t DELAY_BEFORE_SCREEN_CHANGE_MS = 4000;

	CharacterInfoScreenLayout::CharacterInfoScreenLayout(uint16_t width, uint16_t height) :
		BadgerUI::FixedDimensionLayout(width, height)
	{
	}

	void CharacterInfoScreenLayout::onSetup()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		m_Background.setRect(UIRect(UIPoint(0, 0), layoutWidth(), layoutHeight()));
		m_Background.setDrawStyle(ShapeDrawStyle::Filled);
		m_Background.setFillColour(ColourProperty(ColourScheme::Colour_Background));
		addItemToTail(&m_Background);

		setLabelRowPositions(0, m_NameKey, m_NameValue);
		setLabelRowPositions(1, m_SpeciesKey, m_SpeciesValue);
		setLabelRowPositions(2, m_SocialMediaKey, m_SocialMediaValue);

		setLabelCommonProperties(m_NameKey);
		m_NameKey.setText("Name:");
		addItemToTail(&m_NameKey);

		setLabelCommonProperties(m_NameValue);
		m_NameValue.setText("Sample Name");
		addItemToTail(&m_NameValue);
	}

	void CharacterInfoScreenLayout::onActivate()
	{
		m_ButtonReleaseTime = 0;
	}

	void CharacterInfoScreenLayout::onPreUpdate(const BadgerUI::UIUpdateContext& context)
	{
		if ( (m_ButtonReleaseTime == 0 && context.buttons->isReleased(Input::ButtonMain)) ||
			 context.buttons->wasReleasedThisFrame(Input::ButtonMain) )
		{
			m_ButtonReleaseTime = context.currentTimeMs;
		}

		if ( m_ButtonReleaseTime > 0 && context.currentTimeMs - m_ButtonReleaseTime >= DELAY_BEFORE_SCREEN_CHANGE_MS )
		{
			UIModule::setNextScreen(UIModuleResources::ScreenID::MainScreen);
		}
	}

	void CharacterInfoScreenLayout::setLabelCommonProperties(BadgerUI::Label& label)
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		label.setFont(UIModule::resourcesObject().getFont(FontID::ArialSmall));
		label.setFillColour(ColourProperty(ColourScheme::Colour_Background));
		label.setDrawStyle(BadgerGL::ShapeDrawStyle::Filled);
	}

	void CharacterInfoScreenLayout::setLabelRowPositions(uint32_t index, BadgerUI::Label& key, BadgerUI::Label& value)
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		const uint16_t yOffset = PADDING + (index * ROW_HEIGHT);
		const uint16_t fullWidth = (layoutWidth() - (2 * PADDING));
		const uint16_t keyWidth = fullWidth / 3;

		key.setRect(UIRect(UIPoint(PADDING, yOffset), keyWidth, ROW_HEIGHT));
		key.setHorizontalAlignment(HAlignment::Right);
		key.setVerticalAlignment(VAlignment::Centre);

		value.setRect(UIRect(UIPoint(PADDING + keyWidth + KEY_VALUE_SPACING, yOffset), fullWidth - keyWidth - KEY_VALUE_SPACING, ROW_HEIGHT));
		value.setHorizontalAlignment(HAlignment::Left);
		value.setVerticalAlignment(VAlignment::Centre);
	}
}
