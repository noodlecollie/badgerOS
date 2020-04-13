#include <CoreUtil/BgrsAssert.h>
#include <BadgerMath/Rect2DOperations.h>
#include "BitmapBlitter.h"

namespace BadgerGL
{
	void BitmapBlitter::setSource(const ConstBitmapSurface* source, const SurfaceRect& rect)
	{
		m_Source = source;
		m_SourceRect = rect;
	}

	void BitmapBlitter::setDest(BitmapSurface* dest, const Rect16& rect)
	{
		m_Dest = dest;
		m_DestRect = rect;
	}

	void BitmapBlitter::blit()
	{
		if ( !m_Source || !m_Dest || !m_Source->isValid() || !m_Dest->isValid() || m_Dest->hasPalette() )
		{
			return;
		}

		chooseRects();
		clipRects();

		if ( m_SourceRect.isEmpty() || m_DestRect.isEmpty() )
		{
			return;
		}

		if ( !m_Source->hasPalette() && *m_Source->pixelFormat() == *m_Dest->pixelFormat() )
		{
			blitMatchingPixelFormats();
		}
		else
		{
			blitNonMatchingPixelFormats();
		}
	}

	void BitmapBlitter::chooseRects()
	{
		if ( m_SourceRect.isEmpty() )
		{
			// Source rect is not valid, so use entire bitmap.
			m_SourceRect = m_Source->bounds();
		}

		m_SourceRect.ensureMinMaxOrdered();
		m_DestRect.ensureMinMaxOrdered();

		if ( m_DestRect.isEmpty() )
		{
			// Dest rect is not valid, so treat as the source bitmap rect positioned at the original min.
			m_DestRect.setP1(m_DestRect.p0() + Point16(m_SourceRect.width(), m_SourceRect.height()));
		}
	}

	void BitmapBlitter::clipRects()
	{
		// First of all, make sure that the source rect actually fits on its bitmap.
		BadgerMath::trimToBounds(m_SourceRect, m_Source->bounds());

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

	void BitmapBlitter::blitMatchingPixelFormats()
	{
		const uint8_t sourceByteDepth = m_Source->byteDepth();
		const size_t sourceRectHeight = m_SourceRect.height();
		const uint8_t destByteDepth = m_Dest->byteDepth();
		const size_t destRectHeight = m_DestRect.height();

		for ( uint32_t row = 0; row < destRectHeight; ++row )
		{
			const uint16_t sourceRow = (m_InitialSourceOffset.y() + row) % sourceRectHeight;
			const uint8_t* const sourceBegin = static_cast<const uint8_t*>(m_Source->constRawPixelData(m_SourceRect.p0().x(), sourceRow));
			const uint8_t* sourceCursor = sourceBegin + m_InitialSourceOffset.x();
			const uint8_t* sourceEnd = sourceBegin + (m_SourceRect.width() * sourceByteDepth);

			uint8_t* destCursor = static_cast<uint8_t*>(m_Dest->rawPixelData(m_DestRect.p0().x(), m_DestRect.p0().y() + row));
			uint8_t* const destEnd = destCursor + (m_DestRect.width() * destByteDepth);

			while ( destCursor < destEnd )
			{
				const size_t pixelDataBytes = std::min<size_t>(sourceEnd - sourceCursor, destEnd - destCursor);
				memcpy(destCursor, sourceCursor, pixelDataBytes);

				destCursor += pixelDataBytes;
				sourceCursor = sourceBegin;
			}
		}
	}

	void BitmapBlitter::blitNonMatchingPixelFormats()
	{
		BGRS_ASSERT(false, "Blitting non-matching pixel formats is not yet implemented!");
	}
}
