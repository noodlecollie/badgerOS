#pragma once

#include <BadgerGL/FontCharacterGroupContainer.h>
#include <BadgerGL/StaticDataFontCharacterGroup.h>

namespace BadgerUI
{
	class ArialSmallFontData : public BadgerGL::FontCharacterGroupContainer
	{
	public:
		static ArialSmallFontData* StaticInstance();

		inline ArialSmallFontData()
		{
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
