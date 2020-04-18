#include <BadgerMath/Rect2DOperations.h>
#include "BaseBlitter.h"

namespace BadgerGL
{
	void BaseBlitter::setSourceRect(const SurfaceRect& rect)
	{
		m_SourceRect = rect;
	}

	void BaseBlitter::setDest(BitmapSurface* dest, const Rect16& rect)
	{
		m_Dest = dest;
		m_DestRect = rect;
	}

	const BaseBlitter::SurfaceRect& BaseBlitter::sourceRect() const
	{
		return m_SourceRect;
	}

	const Rect16& BaseBlitter::destRect() const
	{
		return m_DestRect;
	}

	void BaseBlitter::chooseRects(const SurfaceRect& sourceBounds)
	{
		if ( m_SourceRect.isEmpty() )
		{
			// Source rect is not valid, so use entire bitmap.
			m_SourceRect = sourceBounds;
		}

		m_SourceRect.ensureMinMaxOrdered();
		m_DestRect.ensureMinMaxOrdered();

		if ( m_DestRect.isEmpty() )
		{
			// Dest rect is not valid, so treat as the source bitmap rect positioned at the original min.
			m_DestRect.setP1(m_DestRect.p0() + Point16(m_SourceRect.width(), m_SourceRect.height()));
		}
	}

	void BaseBlitter::clipRects(const SurfaceRect& sourceBounds)
	{
		// First of all, make sure that the source rect actually fits on its bitmap.
		BadgerMath::trimToBounds(m_SourceRect, sourceBounds);

		// Then make sure that the dest rect fits on the destination bitmap.
		// We keep track of the original min so that we can determine if the
		// dest rect's min was shifted.
		const Point16 origMin(m_DestRect.p0());
		BadgerMath::trimToBounds(m_DestRect, m_Dest->bounds().rect2DCast<Rect16>());

		// If the dest rect min has now been moved inside the dest bitmap, we must store the
		// shift so that we begin drawing the source bitmap from the correct place.
		m_InitialSourceOffset = (m_DestRect.p0() - origMin).vector2DCast<SurfaceVector>();

		// Don't allow the offset to shift out of bound of the source rect.
		m_InitialSourceOffset[0] %= m_SourceRect.width();
		m_InitialSourceOffset[1] %= m_SourceRect.height();
	}
}
