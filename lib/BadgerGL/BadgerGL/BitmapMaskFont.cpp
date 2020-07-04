
#include <CoreUtil/BgrsAssert.h>
#include "BitmapMaskFont.h"

namespace BadgerGL
{
	BitmapMaskFont::BitmapMaskFont(BitmapMask* fontBitmap, const CharInfoBuffer& charDataBuffer) :
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
		return m_CharData.data(index);
	}

	BitmapMaskFont::CharInfo* BitmapMaskFont::charData(const char* stringPtr)
	{
		return stringPtr ? charData(static_cast<size_t>(*stringPtr)) : nullptr;
	}

	const BitmapMaskFont::CharInfo* BitmapMaskFont::charData(size_t index) const
	{
		return m_CharData.constData(index);
	}

	const BitmapMaskFont::CharInfo* BitmapMaskFont::charData(const char* stringPtr) const
	{
		return stringPtr ? charData(static_cast<size_t>(*stringPtr)) : nullptr;
	}

	BitmapMask* BitmapMaskFont::fontBitmap() const
	{
		return m_FontBitmap;
	}
}
