#include <CoreUtil/StringUtil.h>
#include "StringRenderer.h"

namespace BadgerGL
{
	const BitmapMaskFont* StringRenderer::font() const
	{
		return m_Font;
	}

	void StringRenderer::setFont(const BitmapMaskFont* font)
	{
		m_Font = font;
	}

	BitmapMaskBlitter* StringRenderer::blitter() const
	{
		return m_Blitter;
	}

	void StringRenderer::setBlitter(BitmapMaskBlitter* bltr)
	{
		m_Blitter = bltr;
	}

	void StringRenderer::renderString(const char* str, const Rect16& destRect)
	{
		if ( !m_Font ||
			 !str ||
			 !(*str) ||
			 !m_Blitter ||
			 !m_Blitter->destBitmap() ||
			 destRect.isEmpty() )
		{
			return;
		}

		m_Blitter->setSourceBitmap(m_Font->fontBitmap());

		Rect16 targetRect(destRect);
		targetRect.ensureMinMaxOrdered();

		for ( ; *str && targetRect.width() > 0; str = CoreUtil::nextCharUTF8(str) )
		{
			const BitmapMaskFont::CharInfo* chInfo = m_Font->charData(str);

			if ( !chInfo )
			{
				continue;
			}

			drawCharacter(*chInfo, targetRect);

			const size_t widthConsumed = std::min<size_t>(targetRect.width(), chInfo->advance);
			targetRect.setP0(targetRect.p0() + Point16(widthConsumed, 0));
		}
	}

	size_t StringRenderer::calculateStringWidth(const char* str) const
	{
		if ( !m_Font || !str || !(*str) )
		{
			return 0;
		}

		size_t width = 0;

		for ( ; *str; str = CoreUtil::nextCharUTF8(str) )
		{
			const BitmapMaskFont::CharInfo* chInfo = m_Font->charData(str);

			if ( !chInfo )
			{
				continue;
			}

			width += chInfo->advance;
		}

		return width;
	}

	void StringRenderer::drawCharacter(const BitmapMaskFont::CharInfo& chInfo, const Rect16& destRect) const
	{
		Rect16 sourceRect(chInfo.imageRect.rect2DCast<Rect16>());

		// Ensure that the portion of the character image that we get is reduced if drawing
		// it would exceed the destination rectangle.
		Rect16 clipRect(sourceRect.p0() - chInfo.drawOffset, destRect.width(), destRect.height());
		BadgerMath::trimToBounds(sourceRect, clipRect);

		m_Blitter->setSourceRect(sourceRect.rect2DCast<BitmapMaskBlitter::SurfaceRect>());
		m_Blitter->setDestRect(Rect16(destRect.p0() + chInfo.drawOffset, 0, 0));

		m_Blitter->blit();
	}
}
