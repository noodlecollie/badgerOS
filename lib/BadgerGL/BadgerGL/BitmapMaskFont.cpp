
#include <CoreUtil/BgrsAssert.h>
#include <StringLib/StringUtils.h>
#include "BitmapMaskFont.h"

namespace BadgerGL
{
	BitmapMaskFont::BitmapMaskFont(const BitmapMask* fontBitmap, const CharInfoBuffer& charDataBuffer) :
		m_FontBitmap(fontBitmap),
		m_CharData(charDataBuffer)
	{
	}

	bool BitmapMaskFont::isValid() const
	{
		return m_FontBitmap && m_FontBitmap->isValid() && m_CharData.isValid();
	}

	size_t BitmapMaskFont::charCount() const
	{
		return m_CharData.elementCount();
	}

	BitmapMaskFont::CharInfo* BitmapMaskFont::charData(size_t index)
	{
		if ( index >= m_CharData.elementCount() && m_CharData.elementCount() > 0 )
		{
			CharInfo* invalid = m_CharData.data(0);

			if ( invalid->hasImage() )
			{
				return invalid;
			}
		}

		return m_CharData.data(index);
	}

	BitmapMaskFont::CharInfo* BitmapMaskFont::charData(const char* stringPtr)
	{
		// TODO: Handle UTF-8 - we may need to refer to multiple bytes.
		return stringPtr ? charData(static_cast<size_t>(*stringPtr)) : nullptr;
	}

	const BitmapMaskFont::CharInfo* BitmapMaskFont::charData(size_t index) const
	{
		if ( index >= m_CharData.elementCount() && m_CharData.elementCount() > 0 )
		{
			const CharInfo* invalid = m_CharData.constData(0);

			if ( invalid->hasImage() )
			{
				return invalid;
			}
		}

		return m_CharData.constData(index);
	}

	const BitmapMaskFont::CharInfo* BitmapMaskFont::charData(const char* stringPtr) const
	{
		return stringPtr ? charData(StringLib::charCodePointUTF8(stringPtr)) : nullptr;
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

	const BitmapMaskFont::CharInfoBuffer& BitmapMaskFont::charDataBuffer() const
	{
		return m_CharData;
	}

	void BitmapMaskFont::setCharDataBuffer(const CharInfoBuffer& buffer)
	{
		m_CharData = buffer;
	}
}
