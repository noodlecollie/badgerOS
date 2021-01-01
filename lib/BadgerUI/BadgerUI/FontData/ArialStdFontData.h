#pragma once

#include <BadgerUI/FontData/BaseFontData.h>
#include <BadgerGL/StaticDataFontCharacterGroup.h>
#include <Resources/Fonts/ArialStdFont.h>
#include <Resources/Images/ArialStdBitmap.h>

namespace BadgerUI
{
	class ArialStdFontData : public BaseFontData, public StaticFontData<ArialStdFontData>
	{
	public:
		inline ArialStdFontData()
		{
			setFontBitmap(&Resources::ArialStdBitmap::BITMAP);
			setBMFData(Resources::ArialStdFont::BLOB);

			addGroup(&m_InvalidGlyph);
			addGroup(&m_Group1);
			addGroup(&m_Group2);
		}

	private:
		BadgerGL::StaticDataFontCharacterGroup<StringLib::LatinAndLatinSupplement, 0, 0> m_InvalidGlyph;
		BadgerGL::StaticDataFontCharacterGroup<StringLib::LatinAndLatinSupplement, 32, 255> m_Group1;
		BadgerGL::StaticDataFontCharacterGroup<StringLib::LatinExtendedA, 82, 83> m_Group2;
	};
}
