
#include <CoreUtil/BgrsAssert.h>
#include <StringLib/StringUtils.h>
#include <BadgerGL/BitmapMaskFont.h>

namespace BadgerGL
{
	BitmapMaskFont::BitmapMaskFont(const BitmapMask* fontBitmap, const FontCharacterGroupContainer* charContainer) :
		m_FontBitmap(fontBitmap),
		m_CharContainer(charContainer)
	{
	}

	bool BitmapMaskFont::isValid() const
	{
		return m_FontBitmap && m_FontBitmap->isValid() && m_CharContainer;
	}

	const FontCharacterInfo* BitmapMaskFont::characterInfo(size_t index) const
	{
		if ( !m_CharContainer )
		{
			return nullptr;
		}

		const FontCharacterInfo* charInfo = m_CharContainer->charInfo(index);
		return charInfo ? charInfo : m_CharContainer->invalidGlyphInfo();
	}

	const FontCharacterInfo* BitmapMaskFont::characterInfo(const char* stringPtr) const
	{
		return stringPtr ? characterInfo(StringLib::charCodePointUTF8(stringPtr)) : nullptr;
	}

	const BitmapMask* BitmapMaskFont::fontBitmap() const
	{
		return m_FontBitmap;
	}

	void BitmapMaskFont::setFontBitmap(const BitmapMask* bitmap)
	{
		m_FontBitmap = bitmap;
	}

	uint16_t BitmapMaskFont::lineHeight() const
	{
		return m_LineHeight;
	}

	void BitmapMaskFont::setLineHeight(uint16_t height)
	{
		m_LineHeight = height;
	}

	const FontCharacterGroupContainer* BitmapMaskFont::charContainer() const
	{
		return m_CharContainer;
	}

	void BitmapMaskFont::setCharContainer(const FontCharacterGroupContainer* charContainer)
	{
		m_CharContainer = charContainer;
	}
}
