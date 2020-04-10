#include "BitmapBlitOperations.h"

namespace BadgerGL
{
	namespace BitmapBlit
	{
		void blitRowNonMatchingDepth(BitmapSurface& dest, const SurfaceVector& destPos, const BlitSourceParameters& params)
		{
			static constexpr size_t ROW_DATA_LENGTH = 64;
			static uint8_t staticRowData[ROW_DATA_LENGTH];

			BGRS_ASSERTD(dest.isValid(), "Bitmap was not valid");
			BGRS_ASSERTD(params.isValid(), "Source parameters were not valid");

			const uint8_t destByteDepth = dest.byteDepth();

			// The rowData buffer will hold a portion of pixels converted from the source format to the destination format.
			// Calculate the maximum number of destination pixels it can hold.
			const size_t maxPixelsInRow = ROW_DATA_LENGTH / destByteDepth;

			// Iterate over the incoming row in chunks, until there are no more pixels to copy.
			for ( uint16_t sourceRowBase = 0; sourceRowBase < params.rowWidthInPixels; sourceRowBase += maxPixelsInRow )
			{
				BlitSourceParameters localParams;
				localParams.byteDepth = params.byteDepth;

				// Determine how many pixels we can copy on this iteration.
				localParams.rowWidthInPixels = std::min(maxPixelsInRow, params.rowWidthInPixels - sourceRowBase);

				// Determine the location to copy from.
				localParams.rowData = params.rowData + (sourceRowBase * params.byteDepth);

				// Blit to the intermediate buffer. This will handle the difference in byte depths.
				blitToBuffer(staticRowData, destByteDepth, localParams);

				// Write our prepared data into the target bitmap.
				dest.blitHLine(destPos + SurfaceVector(sourceRowBase, 0), staticRowData, localParams.rowWidthInPixels * destByteDepth);
			}
		}

		void blitRowViaPalette(BitmapSurface& dest, const SurfaceVector& destPos, const BitmapSurface& source, const SurfaceRect& sourceRow)
		{
			static constexpr size_t ROW_DATA_LENGTH = 64;
			static uint8_t staticRowData[ROW_DATA_LENGTH];

			BGRS_ASSERTD(dest.isValid(), "Bitmap was not valid");
			BGRS_ASSERTD(source.isValid(), "Source was not valid.");
			BGRS_ASSERTD(source.hasPalette(), "Source did not have a palette.");

			const uint8_t colourByteDepth = source.paletteByteDepth();
			const size_t rowWidthInPixels = sourceRow.width();
			const size_t paletteLength = source.paletteLength();

			// We need to convert palette indices to pixels. Work out how many we can store in the static buffer.
			const size_t maxPixelsInRow = ROW_DATA_LENGTH / colourByteDepth;

			// Iterate over the row in chunks.
			for ( uint16_t sourceRowBase = 0; sourceRowBase < rowWidthInPixels; sourceRowBase += maxPixelsInRow )
			{
				// Determine how many pixels we can process in this iteration.
				const size_t numPixelsInRow = std::min(maxPixelsInRow, rowWidthInPixels - sourceRowBase);

				// Get pointers to the source and destination memory.
				const uint8_t* const pixelData = source.pixelData<uint8_t>(sourceRow.p0().x() + sourceRowBase, sourceRow.p0().y());
				uint8_t* const colourData = staticRowData;

				// Make sure that the destination starts out zeroed, just in case.
				memset(colourData, 0, numPixelsInRow * colourByteDepth);

				for ( uint32_t pixelIndex = 0; pixelIndex < numPixelsInRow; ++pixelIndex )
				{
					const uint8_t paletteIndex = pixelData[pixelIndex];

					// Shouldn't fail this test if the bitmap is in a valid format, but it's here for safety.
					// If the value is out of range, the colour will be left at zero.
					if ( paletteIndex < paletteLength )
					{
						const uint8_t* colour = static_cast<const uint8_t*>(source.rawPaletteData(paletteIndex));
						memcpy(colourData + pixelIndex, colour, colourByteDepth);
					}
				}

				// Now that the data is converted, write the converted data to the target bitmap.
				const BlitSourceParameters params(colourByteDepth, numPixelsInRow, staticRowData);

				if ( colourByteDepth == dest.byteDepth() )
				{
					blitRowMatchingDepth(dest, destPos, params);
				}
				else
				{
					blitRowNonMatchingDepth(dest, destPos, params);
				}
			}
		}
	}
}
