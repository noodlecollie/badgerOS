#include "UIModuleResources.h"
#include "InputModule.h"

namespace Badge
{
	UIModuleResources::UIModuleResources() :
		mainScreen(SSD1351::OLED_WIDTH, SSD1351::OLED_HEIGHT)
	{
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
		mainScreen.setup();
	}

	void UIModuleResources::loop(CoreUtil::TimevalMs currentTime)
	{
		if ( !updateUI(currentTime) )
		{
			return;
		}

		renderUI();
	}

	bool UIModuleResources::updateUI(CoreUtil::TimevalMs currentTime)
	{
		using namespace BadgerUI;

		UIUpdateContext updateContext;
		updateContext.currentTimeMs = currentTime;
		updateContext.buttons = &InputModule::Buttons();

		mainScreen.updateItems(updateContext);

		return mainScreen.dirtyState() != DrawableDirtyState::NotDirty;
	}

	void UIModuleResources::renderUI()
	{
		using namespace BadgerUI;
		using namespace BadgerGL;

		BitmapRenderer renderer(&screenBufferSurface);

		UIDrawContext drawContext;
		drawContext.colourScheme = &colScheme;
		drawContext.renderer = &renderer;
		drawContext.screenBuffer = &screenBufferSurface;
		drawContext.fontDirectory = &fontDirectory;

		switch ( mainScreen.dirtyState() )
		{
			case DrawableDirtyState::ContainerDirty:
			{
				mainScreen.drawAllItems(drawContext);
				break;
			}

			case DrawableDirtyState::ItemDirty:
			{
				mainScreen.drawDirtyItems(drawContext);
				break;
			}

			default:
			{
				break;
			}
		}

		if ( renderer.dirtyArea().isNull() )
		{
			return;
		}

		// For now, just send the whole screen buffer if anything is dirty.
		// This requires less overhead than converting the dirty area into consecutive bytes.
		SSD1351::Driver.writeImage(CoreUtil::ConstBlob(screenBufferSurface.rawPixelData(), screenBufferSurface.pixelDataSize()));
	}
}
