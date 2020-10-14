#include <Arduino.h>
#include <Resources/Fonts/ArialStdFont.h>
#include <BadgerUI/FontDirectory.h>
#include <BadgerUI/ColourScheme.h>
#include "CharacterInfoScreenLayout.h"
#include "../UIModule.h"
#include "../InputModule.h"
#include "../InputDefs.h"
#include "../Languages/Languages.h"

namespace Badge
{
	static constexpr uint16_t PADDING = 5;
	static constexpr uint16_t KEY_COL_WIDTH = 41;
	static constexpr uint16_t KEY_VALUE_SPACING = 5;
	static constexpr uint16_t ROW_HEIGHT = 24;

	static constexpr size_t DELAY_BEFORE_SCREEN_CHANGE_MS = 5000;

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
		m_NameKey.setText(TR_CharacterInfo::LABEL_NAME);
		addItemToTail(&m_NameKey);

		setLabelCommonProperties(m_NameValue);
		m_NameValue.setText("Vesper");
		addItemToTail(&m_NameValue);

		setLabelCommonProperties(m_SpeciesKey);
		m_SpeciesKey.setText(TR_CharacterInfo::LABEL_SPECIES);
		addItemToTail(&m_SpeciesKey);

		setLabelCommonProperties(m_SpeciesValue);
		m_SpeciesValue.setText("Ermine");
		addItemToTail(&m_SpeciesValue);

		setLabelCommonProperties(m_SocialMediaKey);
		m_SocialMediaKey.setText(TR_CharacterInfo::LABEL_SOCIAL_MEDIA);
		addItemToTail(&m_SocialMediaKey);

		setLabelCommonProperties(m_SocialMediaValue);
		m_SocialMediaValue.setText("@x6herbius");
		addItemToTail(&m_SocialMediaValue);

		m_TimeoutBar.setRect(UIRect(UIPoint(0, layoutHeight() - PADDING), layoutWidth(), PADDING));
		m_TimeoutBar.setBackgroundColour(ColourProperty(ColourScheme::Colour_Background));
		m_TimeoutBar.setForegroundColour(ColourProperty(ColourScheme::Colour_Secondary));
		m_TimeoutBar.setOutlineColour(ColourProperty(ColourScheme::Colour_Primary));
		m_TimeoutBar.setFilledFraction(0.0f);
		addItemToTail(&m_TimeoutBar);
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

		const CoreUtil::TimevalMs duration = context.currentTimeMs - m_ButtonReleaseTime;

		if ( context.buttons->isPressed(Input::ButtonMain) )
		{
			m_TimeoutBar.setFilledFraction(1.0f);
		}
		else
		{
			const float filledFraction = (duration < DELAY_BEFORE_SCREEN_CHANGE_MS)
				? 1.0f - (static_cast<float>(duration) / static_cast<float>(DELAY_BEFORE_SCREEN_CHANGE_MS))
				: 0.0f;

			m_TimeoutBar.setFilledFraction(filledFraction);
		}

		if ( m_ButtonReleaseTime > 0 && duration >= DELAY_BEFORE_SCREEN_CHANGE_MS )
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

		key.setRect(UIRect(UIPoint(PADDING, yOffset), KEY_COL_WIDTH, ROW_HEIGHT));
		key.setHorizontalAlignment(HAlignment::Left);
		key.setVerticalAlignment(VAlignment::Centre);

		value.setRect(UIRect(UIPoint(PADDING + KEY_COL_WIDTH + KEY_VALUE_SPACING, yOffset), fullWidth - KEY_COL_WIDTH - KEY_VALUE_SPACING, ROW_HEIGHT));
		value.setHorizontalAlignment(HAlignment::Left);
		value.setVerticalAlignment(VAlignment::Centre);
	}
}
