#include <BadgerMath/Rect2DOperations.h>
#include <BadgerGL/Patterns.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerGL/BitmapBlitter.h>
#include <BadgerGL/BitmapMaskBlitter.h>
#include <BadgerGL/StringRenderer.h>

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

	const URect16& BitmapRenderer::dirtyArea() const
	{
		return m_DirtyArea;
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

	uint8_t BitmapRenderer::bitGradientType() const
	{
		return m_BitGradientType;
	}

	void BitmapRenderer::setBitGradientType(uint8_t type)
	{
		if ( type > MAX_BIT_GRADIENT )
		{
			type = MAX_BIT_GRADIENT;
		}

		m_BitGradientType = type;
	}

	const BitmapMaskFont* BitmapRenderer::font() const
	{
		return m_Font;
	}

	void BitmapRenderer::setFont(const BitmapMaskFont* fnt)
	{
		m_Font = fnt;
	}

	Point16 BitmapRenderer::drawingOffset() const
	{
		return m_DrawingOffset;
	}

	void BitmapRenderer::setDrawingOffset(const Point16& offset)
	{
		m_DrawingOffset = offset;
	}

	void BitmapRenderer::resetDrawingOffset()
	{
		m_DrawingOffset = Point16(0,0);
	}

	void BitmapRenderer::draw(const Rect16& rect)
	{
		if ( !m_Surface )
		{
			return;
		}

		Rect16 localRect(rect + m_DrawingOffset);

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

	void BitmapRenderer::drawPatterned(const Rect16& rect)
	{
		if ( !m_Surface )
		{
			return;
		}

		Rect16 localRect(rect + m_DrawingOffset);

		if ( m_ShapeDrawStyle == ShapeDrawStyle::Outline || m_ShapeDrawStyle == ShapeDrawStyle::FilledOutline )
		{
			drawOutline(localRect);
			BadgerMath::shrink(localRect, m_LineWidth);
		}

		if ( m_ShapeDrawStyle == ShapeDrawStyle::Filled || m_ShapeDrawStyle == ShapeDrawStyle::FilledOutline )
		{
			// TODO: Support left-right gradients

			drawFilled(localRect, m_SecondaryColour);

			VerticalPatternBitmapData data(BIT_GRADIENT[m_BitGradientType]);
			BitmapMask bitmapMask(4, 8, data.constData());

			BitmapMaskBlitter blitter;
			blitter.setSourceBitmap(&bitmapMask);
			blitter.setDest(m_Surface, localRect);
			blitter.setPrimaryColour(m_PrimaryColour);
			blitter.setSecondaryColour(m_SecondaryColour);

			if ( blitter.blit() )
			{
				addToDirtyArea(blitter);
			}
		}
	}

	void BitmapRenderer::fillWithPrimaryColour()
	{
		if ( !m_Surface )
		{
			return;
		}

		fill(m_PrimaryColour);
	}

	void BitmapRenderer::fillWithSecondaryColour()
	{
		if ( !m_Surface )
		{
			return;
		}

		fill(m_SecondaryColour);
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
		blitter.setDest(m_Surface, destRect + m_DrawingOffset);

		if ( blitter.blit() )
		{
			addToDirtyArea(blitter);
		}
	}

	void BitmapRenderer::blitMask(const BitmapMask& source,
								  const Rect16& destRect,
								  const BitmapMask::SurfaceRect& sourceRect,
								  bool drawSecondaryColour)
	{
		if ( !m_Surface )
		{
			return;
		}

		BitmapMaskBlitter blitter;

		blitter.setSource(&source, sourceRect);
		blitter.setDest(m_Surface, destRect + m_DrawingOffset);
		blitter.setPrimaryColour(m_PrimaryColour);
		blitter.setSecondaryColour(m_SecondaryColour);
		blitter.setDrawSecondaryColour(drawSecondaryColour);

		if ( blitter.blit() )
		{
			addToDirtyArea(blitter);
		}
	}

	void BitmapRenderer::drawString(const char* string, const Rect16& destRect, const Point16& adjustment)
	{
		if ( !m_Surface || !m_Font )
		{
			return;
		}

		const Rect16 offsetDest(destRect + m_DrawingOffset);

		BitmapMaskBlitter blitter;
		blitter.setDest(m_Surface, offsetDest);
		blitter.setPrimaryColour(m_PrimaryColour);
		blitter.setSecondaryColour(m_SecondaryColour);

		BadgerGL::StringRenderer stringRenderer;
		stringRenderer.setBlitter(&blitter);
		stringRenderer.setFont(m_Font);

		if ( stringRenderer.renderString(string, offsetDest, adjustment) )
		{
			addToDirtyArea(blitter);
		}
	}

	void BitmapRenderer::fill(uint32_t colour)
	{
		m_Surface->fill(colour);
		m_DirtyArea = m_Surface->bounds();
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

		URect16 screenRect(localRect.rect2DCast<URect16>());

		const bool success = m_Surface->fillRect(screenRect, colour);
		BGRS_ASSERTD(success, "Failed to draw filled rect into bitmap.");

		if ( success )
		{
			addToDirtyArea(screenRect);
		}
	}

	void BitmapRenderer::addToDirtyArea(const URect16& area)
	{
		if ( m_DirtyArea.isNull() )
		{
			m_DirtyArea = area;
		}
		else
		{
			BadgerMath::enlarge(m_DirtyArea, area);
		}
	}

	void BitmapRenderer::addToDirtyArea(const BitmapBlitter& blitter)
	{
		// We use the dest rect as provided by the blitter, as it
		// may have been trimmed during the operation.
		addToDirtyArea(blitter.destRect().rect2DCast<URect16>());
	}

	void BitmapRenderer::addToDirtyArea(const BitmapMaskBlitter& blitter)
	{
		// We use the dest rect as provided by the blitter, as it
		// may have been trimmed during the operation.
		addToDirtyArea(blitter.destRect().rect2DCast<URect16>());
	}
}
