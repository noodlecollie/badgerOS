#pragma once

#include <BadgerUI/Fonts/BaseFont.h>
#include <BadgerGL/StaticDataFontCharacterGroup.h>
#include <Resources/Fonts/ArialStdFont.h>
#include <Resources/Images/ArialStdBitmap.h>

namespace BadgerUI
{
	namespace Fonts
	{
		class ArialStdFont : public BaseFont
		{
		public:
			inline ArialStdFont() :
				BaseFont()
			{
				m_FontBitmap = &Resources::ArialStdBitmap::BITMAP;
				m_BMFData = Resources::ArialStdFont::BLOB;

				m_CharGroupContainer.addGroup(&m_InvalidGlyph);
				m_CharGroupContainer.addGroup(&m_Group1);
				m_CharGroupContainer.addGroup(&m_Group2);

				initialise();
			}

		private:
			BadgerGL::StaticDataFontCharacterGroup<StringLib::LatinAndLatinSupplement, 0, 0> m_InvalidGlyph;
			BadgerGL::StaticDataFontCharacterGroup<StringLib::LatinAndLatinSupplement, 32, 255> m_Group1;
			BadgerGL::StaticDataFontCharacterGroup<StringLib::LatinExtendedA, 82, 83> m_Group2;
		};

		extern const ArialStdFont ArialStd;
	}
}
