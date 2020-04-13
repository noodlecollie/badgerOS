#include <BadgerMath/Rect2DOperations.h>
#include "BitmapRenderer.h"
#include "BitmapBlitter.h"

namespace BadgerGL
{
	using SurfaceVector = ConstBitmapSurface::SurfaceVector;
	using SurfaceRect = ConstBitmapSurface::SurfaceRect;

	BitmapRenderer::BitmapRenderer(BitmapSurface* surface)
	{
		setBitmap(surface);
	}

	BitmapSurface* BitmapRenderer::bitmap() const
	{
		return m_Surface;
	}

	void BitmapRenderer::setBitmap(BitmapSurface* bitmap)
	{
		m_Surface = bitmap;

		if ( m_Surface && m_Surface->hasPalette() )
		{
			BGRS_ASSERTD(false, "Rendering to bitmaps with palettes is not supported.");
			m_Surface = nullptr;
		}
	}

	bool BitmapRenderer::hasBitmap() const
	{
		return m_Surface != nullptr;
	}

	ShapeDrawStyle BitmapRenderer::shapeDrawStyle() const
	{
		return m_ShapeDrawStyle;
	}

	void BitmapRenderer::setShapeDrawStyle(ShapeDrawStyle style)
	{
		m_ShapeDrawStyle = style;
	}

	uint32_t BitmapRenderer::primaryColour() const
	{
		return m_PrimaryColour;
	}

	void BitmapRenderer::setPrimaryColour(uint32_t col)
	{
		m_PrimaryColour = col;
	}

	uint32_t BitmapRenderer::secondaryColour() const
	{
		return m_SecondaryColour;
	}

	void BitmapRenderer::setSecondaryColour(uint32_t col)
	{
		m_SecondaryColour = col;
	}

	uint8_t BitmapRenderer::lineWidth() const
	{
		return m_LineWidth;
	}

	void BitmapRenderer::setLineWidth(uint8_t width)
	{
		m_LineWidth = width;
	}

	void BitmapRenderer::draw(const Rect16& rect)
	{
		if ( !m_Surface )
		{
			return;
		}

		Rect16 localRect(rect);

		if ( m_ShapeDrawStyle == ShapeDrawStyle::Outline || m_ShapeDrawStyle == ShapeDrawStyle::FilledOutline )
		{
			drawOutline(localRect);
			BadgerMath::shrink(localRect, m_LineWidth);
		}

		if ( m_ShapeDrawStyle == ShapeDrawStyle::Filled || m_ShapeDrawStyle == ShapeDrawStyle::FilledOutline )
		{
			drawFilled(localRect, m_ShapeDrawStyle == ShapeDrawStyle::Filled ? m_PrimaryColour : m_SecondaryColour);
		}
	}

	void BitmapRenderer::blit(const ConstBitmapSurface& source,
							  const Rect16& destRect,
							  const SurfaceRect& sourceRect)
	{
		if ( !m_Surface )
		{
			return;
		}

		BitmapBlitter blitter;
		blitter.setSource(&source, sourceRect);
		blitter.setDest(m_Surface, destRect);
		blitter.blit();
	}

	void BitmapRenderer::drawOutline(const Rect16& rect)
	{
		if ( m_LineWidth < 1 )
		{
			return;
		}

		// If the rect itself is too small to have any middle section enclosed by the outline,
		// just fill the lot.
		if ( rect.width() <= 2 * m_LineWidth || rect.height() <= 2 * m_LineWidth )
		{
			drawFilled(rect, m_PrimaryColour);
			return;
		}

		Rect16 localRect;
		const Point16 min = rect.min();
		const size_t width = rect.width();
		const size_t height = rect.height();

		// Draw top edge.
		localRect.setP0(min);
		localRect.setP1(localRect.p0() + Point16(width, m_LineWidth));
		drawFilled(localRect, m_PrimaryColour);

		// Draw bottom edge.
		localRect.setP0(min + Point16(0, height - m_LineWidth));
		localRect.setP1(localRect.p0() + Point16(width, m_LineWidth));
		drawFilled(localRect, m_PrimaryColour);

		// Draw left edge.
		localRect.setP0(min + Point16(0, m_LineWidth));
		localRect.setP1(localRect.p0() + Point16(m_LineWidth, height - (2 * m_LineWidth)));
		drawFilled(localRect, m_PrimaryColour);

		// Draw right edge.
		localRect.setP0(min + Point16(width - m_LineWidth, m_LineWidth));
		localRect.setP1(localRect.p0() + Point16(m_LineWidth, height - (2 * m_LineWidth)));
		drawFilled(localRect, m_PrimaryColour);
	}

	void BitmapRenderer::drawFilled(const Rect16& rect, uint32_t colour)
	{
		Rect16 localRect(rect);
		BadgerMath::trimToBounds(localRect, m_Surface->bounds().rect2DCast<Rect16>());

		if ( localRect.isEmpty() )
		{
			return;
		}

		const bool success = m_Surface->fillRect(localRect.rect2DCast<URect16>(), colour);
		BGRS_ASSERTD(success, "Failed to draw filled rect into bitmap.");
	}
}
