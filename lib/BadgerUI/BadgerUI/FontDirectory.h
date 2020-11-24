#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/EnumAddressableList.h>
#include <CoreUtil/DataBuffer.h>
#include <BadgerGL/BitmapMaskFont.h>
#include <BadgerGL/FontCharacterGroupContainer.h>

namespace BadgerUI
{
	enum class FontID
	{
		ArialStd,
		ArialSmall,

		Count
	};

	struct FontDirectoryEntry
	{
		CoreUtil::ConstBlob bmfData;
		const BadgerGL::BitmapMask* fontBitmap = nullptr;
		BadgerGL::FontCharacterGroupContainer* charGroupContainer = nullptr;
		BadgerGL::BitmapMaskFont fontObject;

		inline bool isValid() const
		{
			// fontObject.isValid() also checks char data and bitmap.
			return bmfData.isValid() && fontObject.isValid();
		}
	};

	// Annoying to have to type out more than once.
	using FontDirectoryBase = CoreUtil::EnumAddressableList<FontDirectoryEntry, FontID, FontID::Count>;


	// TODO: Add addressable list as member rather than inheriting?
	class FontDirectory : private FontDirectoryBase
	{
	public:
		FontDirectory();

		void loadAllFonts();
		const BadgerGL::BitmapMaskFont* getFont(FontID id) const;

	private:
		void initialiseEntries();
	};
}
