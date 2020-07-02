#include <CoreUtil/DataUtil.h>
#include "BitmapMaskBlitter.h"

namespace BadgerGL
{
	void BitmapMaskBlitter::setSource(const BitmapMask* source, const SurfaceRect& rect)
	{
		m_Source = source;
		m_SourceRect = rect;
	}

	void BitmapMaskBlitter::setPrimaryColour(uint32_t col)
	{
		m_PrimaryColour = col;
	}

	void BitmapMaskBlitter::setSecondaryColour(uint32_t col)
	{
		m_SecondaryColour = col;
	}

	void BitmapMaskBlitter::setDrawSecondaryColour(bool draw)
	{
		m_DrawSecondaryColour = draw;
	}

	bool BitmapMaskBlitter::blit()
	{
		if ( !m_Source || !m_Dest || !m_Source->isValid() || !m_Dest->isValid() || m_Dest->hasPalette() )
		{
			return false;
		}

		const SurfaceRect sourceBounds = m_Source->bounds();
		chooseRects(sourceBounds);
		clipRects(sourceBounds);

		if ( m_SourceRect.isEmpty() || m_DestRect.isEmpty() )
		{
			return false;
		}

		blitInternal();
		return true;
	}

	void BitmapMaskBlitter::blitInternal()
	{
		const uint8_t* priCol = reinterpret_cast<const uint8_t*>(&m_PrimaryColour);
		const uint8_t* secCol = reinterpret_cast<const uint8_t*>(&m_SecondaryColour);

		const size_t sourceRectWidth = m_SourceRect.width();
		const size_t sourceRectHeight = m_SourceRect.height();
		const uint8_t destByteDepth = m_Dest->byteDepth();
		const uint8_t destBitDepth = m_Dest->bitDepth();
		const size_t destRectHeight = m_DestRect.height();

		for ( uint32_t row = 0; row < destRectHeight; ++row )
		{
			const uint16_t sourceRow = (m_InitialSourceOffset.y() + row) % sourceRectHeight;
			uint16_t sourceXOffset = m_InitialSourceOffset.x();

			uint8_t* destCursor = static_cast<uint8_t*>(m_Dest->rawPixelData(m_DestRect.p0().x(), m_DestRect.p0().y() + row));
			uint8_t* const destEnd = destCursor + (m_DestRect.width() * destByteDepth);

			while ( destCursor < destEnd )
			{
				const uint8_t value = m_Source->maskValue(m_SourceRect.p0().x() + sourceXOffset, sourceRow);

				if ( value )
				{
					CoreUtil::writeBits(destCursor, priCol, destBitDepth);
				}
				else if ( m_DrawSecondaryColour )
				{
					CoreUtil::writeBits(destCursor, secCol, destBitDepth);
				}

				sourceXOffset = (sourceXOffset + 1) % sourceRectWidth;
				destCursor += destByteDepth;
			}
		}
	}
}
