#include <BadgerMath/Rect2DOperations.h>
#include "BitmapRenderer.h"
#include"BitmapBlitOperations.h"

namespace BadgerGL
{
	using SurfaceVector = BitmapSurface::SurfaceVector;
	using SurfaceRect = BitmapSurface::SurfaceRect;

	BitmapRenderer::BitmapRenderer(BitmapSurface& surface) :
		m_Surface(&surface)
	{
		BGRS_ASSERTD(!m_Surface->hasPalette(), "Rendering to bitmaps with palettes is not supported.");
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

	// TOOD: Maybe factor out the rect clipping logic here one day, so that it can be used for other things too?
	void BitmapRenderer::blit(const BitmapSurface& source,
							  const Point16& pos,
							  const SurfaceRect& sourceRect)
	{
		Rect16 chosenSourceRect((sourceRect.isNull() ? source.bounds() : sourceRect).rect2DCast<Rect16>());
		chosenSourceRect.ensureMinMaxOrdered();

		Rect16 workingRect(chosenSourceRect);

		// Locate the rect at the target position and keep a copy,
		// so that we can compare how much it was clipped by later.
		BadgerMath::translateToPosition(workingRect, pos);
		const Rect16 preClipRect = workingRect.asBounds();

		// Clip the rect to the bounds of the screen.
		BadgerMath::trimToBounds(workingRect, m_Surface->bounds().rect2DCast<Rect16>());

		if ( workingRect.isEmpty() )
		{
			// Nothing to draw.
			return;
		}

		// Work out the deltas for each point.
		const Point16 delta0 = workingRect.p0() - preClipRect.p0();
		const Point16 delta1 = workingRect.p1() - preClipRect.p1();

		// Create a new pos and source rect from these deltas.
		const Point16 newPos = pos + delta0;
		chosenSourceRect.setP0(chosenSourceRect.p0() + delta0);
		chosenSourceRect.setP1(chosenSourceRect.p1() + delta1);

		blitInternal(source,
					 newPos.vector2DCast<SurfaceVector>(),
					 chosenSourceRect.rect2DCast<SurfaceRect>());
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

	void BitmapRenderer::blitInternal(const BitmapSurface& source,
									  const SurfaceVector& pos,
									  const SurfaceRect& sourceRect)
	{
		const size_t sourceWidth = sourceRect.width();
		const size_t sourceHeight = sourceRect.height();
		const bool sourceHasPalette = source.hasPalette();
		const bool depthsMatch = source.byteDepth() == m_Surface->byteDepth();

		for ( uint32_t y = 0; y < sourceHeight; ++y )
		{
			const SurfaceVector offsetVec(0, y);
			const SurfaceRect rowRect(sourceRect.p0() + offsetVec, sourceWidth, 1);

			if ( sourceHasPalette )
			{
				BitmapBlit::blitRowViaPalette(*m_Surface, pos + offsetVec, source, rowRect);
			}
			else if ( depthsMatch )
			{
				BitmapBlit::blitRowMatchingDepth(*m_Surface, pos + offsetVec, BitmapBlit::BlitSourceParameters(source, rowRect));
			}
			else
			{
				BitmapBlit::blitRowNonMatchingDepth(*m_Surface, pos + offsetVec, BitmapBlit::BlitSourceParameters(source, rowRect));
			}
		}
	}
}
