#pragma once

#include <BadgerUI/FontData/BaseFontData.h>
#include <BadgerGL/StaticDataFontCharacterGroup.h>
#include <Resources/Fonts/ArialSmallFont.h>
#include <Resources/Images/ArialSmallBitmap.h>

namespace BadgerUI
{
	class ArialSmallFontData : public BaseFontData, public StaticFontData<ArialSmallFontData>
	{
	public:
		inline ArialSmallFontData()
		{
			setFontBitmap(&Resources::ArialSmallBitmap::BITMAP);
			setBMFData(Resources::ArialSmallFont::BLOB);

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
