#include <Arduino.h>
#include <CoreUtil/ArrayUtil.h>
#include "UIModuleResources.h"
#include "InputModule.h"

namespace Badge
{
	const char* UIModuleResources::screenName(ScreenID id)
	{
#define LIST_ITEM(value, name) name,
		static constexpr const char* const SCREEN_NAMES[Badge::UIModuleResources::ScreenCount] =
		{
			SCREEN_ID_LIST
		};
#undef LIST_ITEM

		return (id >= 0 && id < CoreUtil::arraySize(SCREEN_NAMES))
			? SCREEN_NAMES[id]
			: "Invalid";
	}

	UIModuleResources::UIModuleResources() :
		m_MainScreen(SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT),
		m_CharInfoScreen(SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT)
	{
	}

	void UIModuleResources::setup()
	{
		using namespace BadgerGL;
		using namespace BadgerUI;

		m_ColScheme.setColour(ColourScheme::Colour_Background, col24To16(0x000000));
		m_ColScheme.setColour(ColourScheme::Colour_BackgroundAlt, col24To16(0x534b62));
		m_ColScheme.setColour(ColourScheme::Colour_Primary, col24To16(0xfdfffc));
		m_ColScheme.setColour(ColourScheme::Colour_Secondary, col24To16(0xc0bcb5));

		setUpScreen(m_MainScreen, MainScreen);
		setUpScreen(m_CharInfoScreen, CharacterInfoScreen);
		setNextScreen(MainScreen);
	}

	UIModuleResources::ScreenID UIModuleResources::currentScreen() const
	{
		return static_cast<UIModuleResources::ScreenID>(m_LayoutContainer.activeLayoutIndex());
	}

	void UIModuleResources::setNextScreen(ScreenID id)
	{
		if ( id < InvalidScreen || id >= ScreenCount )
		{
			id = InvalidScreen;
		}

		m_NextScreenID = id;
	}

	MainScreenLayout& UIModuleResources::getMainScreenLayout()
	{
		return m_MainScreen;
	}

	CharacterInfoScreenLayout& UIModuleResources::getCharacterInfoScreenLayout()
	{
		return m_CharInfoScreen;
	}

	void UIModuleResources::loop(CoreUtil::TimevalMs currentTime)
	{
		// If the target screen is not set, swap to it.
		if ( m_LayoutContainer.activeLayoutIndex() != m_NextScreenID )
		{
			Serial.printf("Changing active screen to '%s' (%d)\r\n", screenName(m_NextScreenID), m_NextScreenID);
			m_LayoutContainer.setActiveLayoutIndex(m_NextScreenID);
		}

		bool shouldSendBuffer = false;
		const bool currentScreenValid = m_LayoutContainer.activeLayoutIsValid();

		if ( currentScreenValid )
		{
			shouldSendBuffer = updateUI(currentTime) && renderUI();
		}
		else
		{
			m_ScreenBufferSurface.fill(0x0000);
			shouldSendBuffer = true;
		}

		if ( shouldSendBuffer )
		{
			sendScreenBuffer();
		}
	}

	bool UIModuleResources::updateUI(CoreUtil::TimevalMs currentTime)
	{
		using namespace BadgerUI;

		UIUpdateContext updateContext;
		updateContext.currentTimeMs = currentTime;
		updateContext.buttons = &InputModule::buttons();

		return m_LayoutContainer.updateActiveLayout(updateContext) != DrawableDirtyState::NotDirty;
	}

	bool UIModuleResources::renderUI()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		BitmapRenderer renderer(&m_ScreenBufferSurface);

		UIDrawContext drawContext;
		drawContext.colourScheme = &m_ColScheme;
		drawContext.renderer = &renderer;
		drawContext.screenBuffer = &m_ScreenBufferSurface;

		m_LayoutContainer.renderActiveLayout(drawContext);

		// For now, just send the whole screen buffer if anything is dirty.
		// This requires less overhead than converting the dirty area into consecutive bytes.
		return !renderer.dirtyArea().isNull();
	}
}
