#pragma once

#include <CoreUtil/BgrsAssert.h>
#include "BitmapSurface.h"

namespace BadgerGL
{
	namespace BitmapBlit
	{
		using SurfaceVector = ConstBitmapSurface::SurfaceVector;
		using SurfaceRect = ConstBitmapSurface::SurfaceRect;

		// Used to abstract away from using a bitmap as a source.
		// This allows us to use temporary uint8_t row buffers,
		// for example when converting from a bitmap using a palette.
		struct BlitSourceParameters
		{
			inline BlitSourceParameters()
			{
			}

			inline BlitSourceParameters(uint8_t inByteDepth, size_t inRowWidth, const uint8_t* inData) :
				byteDepth(inByteDepth),
				rowWidthInPixels(inRowWidth),
				rowData(inData)
			{
			}

			inline BlitSourceParameters(const BlitSourceParameters& other) :
				byteDepth(other.byteDepth),
				rowWidthInPixels(other.rowWidthInPixels),
				rowData(other.rowData)
			{
			}

			inline BlitSourceParameters(const ConstBitmapSurface& source, const SurfaceRect& sourceRow) :
				byteDepth(source.byteDepth()),
				rowWidthInPixels(sourceRow.width()),
				rowData(static_cast<const uint8_t*>(source.constRawPixelData(sourceRow.p0().x(), sourceRow.p0().y())))
			{
			}

			inline bool isValid() const
			{
				return byteDepth > 0 &&
					   byteDepth <= bitDepthToByteDepth(ConstBitmapSurface::MAX_BIT_DEPTH) &&
					   rowWidthInPixels > 0 &&
					   rowData != nullptr;
			}

			uint8_t byteDepth = 0;
			size_t rowWidthInPixels = 0;
			const uint8_t* rowData = nullptr;
		};

		// For simplicity and speed, all the functions below assume that their parameters are valid.
		// Arguments should be checked by the caller before calling.
		// The functions are not thread-safe.

		// This function will tile the pixels specified by the source params into the provided buffer.
		// This means that the source pixel row will be repeated as many times as necessary to fill the buffer.
		// If the buffer length is 0, the buffer is assumed to be of length (params.rowWidthInPixels * destByteDepth),
		// in which case the row of source pixels will be written exactly once. The caller should ensure that the
		// buffer is long enough to accept this much data!
		static inline void blitToBuffer(uint8_t* buffer, uint8_t destByteDepth, const BlitSourceParameters& params, size_t bufferLengthInBytes = 0)
		{
			BGRS_ASSERTD(buffer, "Buffer was not valid.");
			BGRS_ASSERTD(destByteDepth > 0 && destByteDepth <= bitDepthToByteDepth(ConstBitmapSurface::MAX_BIT_DEPTH), "Byte depth was not valid.");
			BGRS_ASSERTD(params.isValid(), "Source params were not valid.");

			if ( bufferLengthInBytes < 1 )
			{
				// Assume that the buffer is long enough to hold one complete row, at the target byte depth.
				bufferLengthInBytes = params.rowWidthInPixels * destByteDepth;
			}

			// How many target pixels can the buffer hold?
			const size_t numPixelsWritableInBuffer = bufferLengthInBytes / destByteDepth;

			// Ensure the data starts zeroed, so that garbage doesn't interfere with the copying.
			memset(buffer, 0, bufferLengthInBytes);

			// Create a "cursor" that will iterate over the source data.
			const uint8_t* sourcePixels = params.rowData;

			// Once the cursor reaches or passes this value, it is out of range.
			const uint8_t* const sourcePixelsEnd = sourcePixels + (params.rowWidthInPixels * params.byteDepth);

			// For each pixel in the target buffer:
			for ( uint32_t pixelIndex = 0; pixelIndex < numPixelsWritableInBuffer; ++pixelIndex )
			{
				// We treat the smaller-width pixel as occupying the most significant bytes of the larger-width pixel.
				// If the destination width is larger than the source width, the LSBs will remain zero.
				if ( params.byteDepth > destByteDepth )
				{
					// Copy the most significant bytes from the source pixel.
					memcpy(buffer, sourcePixels + (params.byteDepth - destByteDepth), destByteDepth);
				}
				else
				{
					// Copy the bytes from the source pixel to the most significant bytes of the dest pixel.
					memcpy(buffer + (destByteDepth - params.byteDepth), sourcePixels, params.byteDepth);
				}

				sourcePixels += params.byteDepth;

				// If we have reached the end of the source data, wrap back to the start.
				if ( sourcePixels >= sourcePixelsEnd )
				{
					sourcePixels = params.rowData;
				}

				buffer += destByteDepth;
			}
		}

		static inline void blitRowMatchingDepth(BitmapSurface& dest, const SurfaceVector& destPos, const BlitSourceParameters& params)
		{
			BGRS_ASSERTD(dest.isValid(), "Bitmap was not valid.");
			BGRS_ASSERTD(params.isValid(), "Source params were not valid.");

			dest.blitHLine(destPos, params.rowData, params.rowWidthInPixels * params.byteDepth);
		}

		void blitRowNonMatchingDepth(BitmapSurface& dest, const SurfaceVector& destPos, const BlitSourceParameters& params);
		void blitRowViaPalette(BitmapSurface& dest, const SurfaceVector& destPos, const ConstBitmapSurface& source, const SurfaceRect& sourceRow);
	}
}
