#include <Arduino.h>
#include <BadgerUI/BMFFileReader.h>
#include "FontDirectory.h"

// Fonts:
#include <BadgerUI/FontData/ArialStdFontData.h>
#include <BadgerUI/FontData/ArialSmallFontData.h>

namespace BadgerUI
{
	FontDirectory::FontDirectory() :
		m_FontList(true)
	{
	}

	const BadgerGL::BitmapMaskFont* FontDirectory::getFont(FontID id) const
	{
		const BaseFontData* entry = m_FontList.item(id);
		return entry ? &entry->fontObject() : nullptr;
	}

	void FontDirectory::loadAllFonts()
	{
		using namespace BadgerGL;

		initialiseEntries();

		bool success = true;

		m_FontList.forEach([&success](uint32_t index, BaseFontData* item)
		{
			if ( !item )
			{
				Serial.printf("Font %u was not initialised before loading.", index);
				success = false;
			}
			else if ( !item->initialise() )
			{
				Serial.printf("Font %u was not valid after loading font data.", index);
				success = false;
			}
		});

		if ( !success )
		{
			BGRS_ASSERT(false, "One or more fonts failed to load.");
		}
	}

	void FontDirectory::initialiseEntries()
	{
		addMapping<ArialStdFontData>(FontID::ArialStd);
		addMapping<ArialSmallFontData>(FontID::ArialSmall);
	}
}
