#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/EnumAddressableList.h>
#include <CoreUtil/DataBuffer.h>
#include <BadgerGL/BitmapMaskFont.h>
#include <BadgerGL/FontCharacterGroupContainer.h>
#include <BadgerUI/FontData/BaseFontData.h>

namespace BadgerUI
{
	enum class FontID
	{
		ArialStd,
		ArialSmall,

		Count
	};

	class FontDirectory
	{
	public:
		FontDirectory();

		void loadAllFonts();
		const BadgerGL::BitmapMaskFont* getFont(FontID id) const;

	private:
		using FontList = CoreUtil::EnumAddressableList<BaseFontData*, FontID, FontID::Count>;

		void initialiseEntries();

		template<typename T>
		inline void addMapping(FontID id)
		{
			m_FontList.item(id) = &T::staticInstance();
		}

		FontList m_FontList;
	};
}
