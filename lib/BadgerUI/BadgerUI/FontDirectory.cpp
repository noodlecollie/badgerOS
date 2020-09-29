// Fonts:
#include <Resources/Fonts/ArialStdFont.h>
#include <Resources/Images/ArialStdBitmap.h>
#include <Resources/Fonts/ArialSmallFont.h>
#include <Resources/Images/ArialSmallBitmap.h>

#include <Arduino.h>
#include <BadgerGL/BMFFileReader.h>
#include "FontDirectory.h"

namespace BadgerUI
{
	FontDirectory::FontDirectory() :
		FontDirectoryBase()
	{
		initialiseEntries();
	}

	void FontDirectory::initialiseEntries()
	{
		item(FontID::ArialStd).fontBitmap = &Resources::ArialStdBitmap::BITMAP;
		item(FontID::ArialStd).bmfData = Resources::ArialStdFont::BLOB;

		item(FontID::ArialSmall).fontBitmap = &Resources::ArialSmallBitmap::BITMAP;
		item(FontID::ArialSmall).bmfData = Resources::ArialSmallFont::BLOB;
	}

	void FontDirectory::loadAllFonts()
	{
		using namespace BadgerGL;

		bool success = true;

		forEach([&success](uint32_t index, FontDirectoryEntry& item)
		{
			BMFFileReader reader;

			reader.setCharInfoBuffer(&item.fontCharData);
			reader.setFileData(item.bmfData);

			const BMFFileReader::FileStatus status = reader.validateFile();

			if ( status != BMFFileReader::FileStatus::Valid )
			{
				const uint8_t block = reader.idOfBlockThatFailedValidation();
				const char* const description = BMFFileReader::fileStatusDescription(status);

				Serial.printf("Font %u failed to load. Error: %s. (faulty block ID: %u)\r\n", index, description, block);

				success = false;
				return;
			}

			reader.populateCharInfo();

			item.fontObject.setLineHeight(reader.lineHeight());
			item.fontObject.setCharDataBuffer(item.fontCharData);
			item.fontObject.setFontBitmap(item.fontBitmap);

			if ( !item.fontObject.isValid() )
			{
				Serial.printf("Font %u was not valid after loading font data.", index);
			}
		});

		if ( !success )
		{
			BGRS_ASSERT(false, "One or more fonts failed to load.");
		}
	}

	const BadgerGL::BitmapMaskFont* FontDirectory::getFont(FontID id) const
	{
		return &item(id).fontObject;
	}
}
