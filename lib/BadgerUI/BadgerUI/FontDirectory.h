#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/EnumAddressableList.h>
#include <CoreUtil/DataBuffer.h>
#include <BadgerGL/BitmapMaskFont.h>

namespace BadgerUI
{
	enum class FontID
	{
		ArialStd,

		Count
	};

	// This will need to be expanded later, when we add better character support.
	using ASCIIFontDataBuffer = CoreUtil::StaticDataBuffer<BadgerGL::BitmapMaskFont::CharInfo, 128>;

	struct FontDirectoryEntry
	{
		CoreUtil::ConstBlob bmfData;
		const BadgerGL::BitmapMask* fontBitmap = nullptr;
		ASCIIFontDataBuffer fontCharData;
		BadgerGL::BitmapMaskFont fontObject;

		inline bool isValid() const
		{
			// fontObject.isValid() also checks char data and bitmap.
			return bmfData.isValid() && fontObject.isValid();
		}
	};

	// Annoying to have to type out more than once.
	using FontDirectoryBase = CoreUtil::EnumAddressableList<FontDirectoryEntry, FontID, FontID::Count>;

	class FontDirectory : public FontDirectoryBase
	{
	public:
		FontDirectory();

		void loadAllFonts();

	private:
		void initialiseEntries();

#ifdef DEBUG
		inline void validateEntries()
		{
			forEach([](uint32_t index, const FontDirectoryEntry& item)
			{
				BGRS_ASSERT(item.isValid(), "An entry in the font directory was not set up correctly.");
			});
		}
#endif
	};
}
