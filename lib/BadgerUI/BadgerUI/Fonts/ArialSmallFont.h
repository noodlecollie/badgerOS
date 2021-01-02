#pragma once

#include <BadgerUI/Fonts/BaseFont.h>
#include <BadgerGL/StaticDataFontCharacterGroup.h>
#include <Resources/Fonts/ArialSmallFont.h>
#include <Resources/Images/ArialSmallBitmap.h>

namespace BadgerUI
{
	namespace Fonts
	{
		class ArialSmallFont : public BaseFont
		{
		public:
			inline ArialSmallFont() :
				BaseFont()
			{
				m_FontBitmap = &Resources::ArialSmallBitmap::BITMAP;
				m_BMFData = Resources::ArialSmallFont::BLOB;

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

		extern ArialSmallFont ArialSmall;
	}
}
