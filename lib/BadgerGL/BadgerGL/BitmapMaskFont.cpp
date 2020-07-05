
#include <CoreUtil/BgrsAssert.h>
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
		// TODO: Handle UTF-8.
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
		// TODO: Handle UTF-8.
		return stringPtr ? charData(static_cast<size_t>(*stringPtr)) : nullptr;
	}

	const BitmapMask* BitmapMaskFont::fontBitmap() const
	{
		return m_FontBitmap;
	}
}
