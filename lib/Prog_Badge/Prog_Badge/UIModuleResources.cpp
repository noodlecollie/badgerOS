#include "UIModuleResources.h"
#include "InputModule.h"

namespace Badge
{
	UIModuleResources::UIModuleResources() :
		mainScreen(SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT),
		charInfoScreen(SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT)
	{
		memset(m_Screens, 0, sizeof(m_Screens));
	}

	void UIModuleResources::setup()
	{
		using namespace BadgerGL;
		using namespace BadgerUI;

		colScheme.setColour(ColourScheme::Colour_Background, col24To16(0x000000));
		colScheme.setColour(ColourScheme::Colour_BackgroundAlt, col24To16(0x534b62));
		colScheme.setColour(ColourScheme::Colour_Primary, col24To16(0xfdfffc));
		colScheme.setColour(ColourScheme::Colour_Secondary, col24To16(0xc0bcb5));

		fontDirectory.loadAllFonts();

		setUpScreen(mainScreen, MainScreen);
		setUpScreen(charInfoScreen, CharacterInfoScreen);
		setCurrentScreen(MainScreen);
	}

	UIModuleResources::ScreenID UIModuleResources::currentScreen() const
	{
		return m_CurrentScreen;
	}

	void UIModuleResources::setCurrentScreen(ScreenID id)
	{
		if ( id < InvalidScreen || id >= ScreenCount )
		{
			id = InvalidScreen;
		}

		m_CurrentScreen = id;
	}

	void UIModuleResources::loop(CoreUtil::TimevalMs currentTime)
	{
		bool shouldSendBuffer = false;
		const bool currentScreenValid = m_CurrentScreen >= 0 && m_CurrentScreen < ScreenCount && m_Screens[m_CurrentScreen];

		if ( currentScreenValid )
		{
			BadgerUI::BaseLayout& screen = *(m_Screens[m_CurrentScreen]);
			shouldSendBuffer = updateUI(screen, currentTime) && renderUI(screen);
		}
		else
		{
			screenBufferSurface.fill(0x0000);
			shouldSendBuffer = true;
		}

		if ( shouldSendBuffer )
		{
			sendScreenBuffer();
		}
	}

	bool UIModuleResources::updateUI(BadgerUI::BaseLayout& screen, CoreUtil::TimevalMs currentTime)
	{
		using namespace BadgerUI;

		UIUpdateContext updateContext;
		updateContext.currentTimeMs = currentTime;
		updateContext.buttons = &InputModule::buttons();

		screen.updateItems(updateContext);

		return screen.dirtyState() != DrawableDirtyState::NotDirty;
	}

	bool UIModuleResources::renderUI(BadgerUI::BaseLayout& screen)
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		BitmapRenderer renderer(&screenBufferSurface);

		UIDrawContext drawContext;
		drawContext.colourScheme = &colScheme;
		drawContext.renderer = &renderer;
		drawContext.screenBuffer = &screenBufferSurface;
		drawContext.fontDirectory = &fontDirectory;

		switch ( screen.dirtyState() )
		{
			case DrawableDirtyState::ContainerDirty:
			{
				screen.drawAllItems(drawContext);
				break;
			}

			case DrawableDirtyState::ItemDirty:
			{
				screen.drawDirtyItems(drawContext);
				break;
			}

			default:
			{
				break;
			}
		}

		// For now, just send the whole screen buffer if anything is dirty.
		// This requires less overhead than converting the dirty area into consecutive bytes.
		return !renderer.dirtyArea().isNull();
	}
}
