#include <CoreUtil/StringUtil.h>
#include "StringRenderer.h"

namespace BadgerGL
{
	size_t StringRenderer::calculateStringWidth(const BitmapMaskFont* font, const char* str)
	{
		StringRenderer renderer;
		renderer.setFont(font);
		return renderer.calculateStringWidth(str);
	}

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

	bool StringRenderer::renderString(const char* str, const Rect16& destRect, int16_t xShift)
	{
		if ( !m_Font ||
			 !str ||
			 !(*str) ||
			 !m_Blitter ||
			 !m_Blitter->destBitmap() ||
			 destRect.isEmpty() ||
			 xShift >= static_cast<int16_t>(destRect.width()) )
		{
			return false;
		}

		m_Blitter->setSourceBitmap(m_Font->fontBitmap());

		// Create a mutable rect. This will resize based on the unused space after the written characters.
		Rect16 targetRect(destRect);
		targetRect.ensureMinMaxOrdered();

		// Make a note of the left hand boundary of the target drawing area.
		// If we can determine that a character would be drawn entirely left of this
		// boundary, we don't need to draw it at all.
		const int16_t leftDrawingBorder = targetRect.p0().x();

		// Account for X shift. We have ensured that this will not be so large in the
		// positive direction that it would exceed the width of the dest rect.
		targetRect.setP0(targetRect.p0() + Point16(xShift, 0));

		bool renderedCharacters = false;

		for ( ; *str && targetRect.width() > 0; str = CoreUtil::nextCharUTF8(str) )
		{
			const BitmapMaskFont::CharInfo* chInfo = m_Font->charData(str);

			if ( !chInfo )
			{
				continue;
			}

			// Only bother drawing if the character is in the dest rect.
			if ( targetRect.p0().x() + chInfo->imageRect.width() > leftDrawingBorder )
			{
				drawCharacter(*chInfo, targetRect);
				renderedCharacters = true;
			}

			const size_t widthConsumed = std::min<size_t>(targetRect.width(), chInfo->advance);
			targetRect.setP0(targetRect.p0() + Point16(widthConsumed, 0));
		}

		return renderedCharacters;
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
