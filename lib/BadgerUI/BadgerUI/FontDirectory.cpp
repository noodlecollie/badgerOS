// Fonts:
#include <Resources/Fonts/ArialStdFont.h>
#include <Resources/Images/ArialStdBitmap.h>

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
	}

	void FontDirectory::finaliseEntries()
	{
		forEach([](uint32_t index, FontDirectoryEntry& item)
		{
			item.fontObject.setCharDataBuffer(item.fontCharData);
			item.fontObject.setFontBitmap(item.fontBitmap);

			if ( !item.isValid() )
			{
				Serial.printf("Font %u validation failed.\n", index);
				BGRS_ASSERT(false, "An entry in the font directory was not set up correctly.");
			}
		});
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

				Serial.printf("Font %u failed to load. Error: %s. (faulty block ID: %u)\n", index, description, block);

				success = false;
				return;
			}

			reader.populateCharInfo();
		});

		if ( !success )
		{
			BGRS_ASSERT(false, "One or more fonts failed to load.");
		}
	}
}
