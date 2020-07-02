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

	bool BitmapBlitter::blit()
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

		const bool pixelFormatsMatch =
			(m_Source->hasPalette() && *m_Source->palettePixelFormat() == *m_Dest->pixelFormat()) ||
			(!m_Source->hasPalette() && *m_Source->pixelFormat() == *m_Dest->pixelFormat());

		if ( pixelFormatsMatch )
		{
			blitMatchingPixelFormats();
		}
		else
		{
			blitNonMatchingPixelFormats();
		}

		return true;
	}

	void BitmapBlitter::blitMatchingPixelFormats()
	{
		const bool sourceUsesPalette = m_Source->hasPalette();
		const uint8_t sourceByteDepth = m_Source->byteDepth();
		const uint8_t sourcePaletteByteDepth = m_Source->paletteByteDepth();
		const uint16_t sourcePaletteLength = m_Source->paletteLength();
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
				size_t sourceRowColourBytes = sourceEnd - sourceCursor;

				if ( sourceUsesPalette )
				{
					// The distance between the pointers will be in palette indices (1 byte each).
					// To work out how much space the colours will take, we need to multiply this by
					// the palette byte depth.
					sourceRowColourBytes *= sourcePaletteByteDepth;
				}

				const size_t pixelDataBytes = std::min<size_t>(sourceRowColourBytes, destEnd - destCursor);

				if ( sourceUsesPalette )
				{
					for ( size_t bytesWritten = 0; bytesWritten < pixelDataBytes; bytesWritten += sourcePaletteByteDepth )
					{
						// Get the index into the palette from the image.
						const uint8_t paletteIndex = *(sourceCursor++);

						if ( paletteIndex < sourcePaletteLength )
						{
							// Get a pointer to the palette data and write this colour to the destination.
							const uint8_t* const paletteColour = static_cast<const uint8_t*>(m_Source->constRawPaletteData(paletteIndex));
							memcpy(destCursor + bytesWritten, paletteColour, sourcePaletteByteDepth);
						}
					}
				}
				else
				{
					memcpy(destCursor, sourceCursor, pixelDataBytes);
				}

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
