#pragma once

#include <CoreUtil/Blob.h>
#include "PixelFormat.h"
#include "BitmapBuffer.h"

namespace BadgerGL
{
	struct PixelFormatConverter
	{
		inline bool isValid(PixelFormatId expectedDestType) const
		{
			return destType == expectedDestType && canConvert && convertValue && convertPixels && convertPixelsViaPalette;
		}

		// Format that this converter converts to.
		PixelFormatId destType;

		// Returns true if the given format can be converted to the destingation format, or false otherwise.
		bool (*canConvert)(PixelFormatId id);

		// Converts an individual colour value to the destination format.
		bool (*convertValue)(uint32_t& dest, uint32_t source, PixelFormatId destFormat);

		// Converts the source pixels to the destination format.
		// Assumes that the destination buffer format matches destType.
		bool (*convertPixels)(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer);

		// Same as above, but looks up the colours for each pixel in the source buffer via the palette.
		// Assumes that the source buffer has a pixel format of Mono256.
		bool (*convertPixelsViaPalette)(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer, const ConstBitmapBuffer& palette);
	};

	const PixelFormatConverter* getPixelFormatConverter(PixelFormatId destType);

	// Returns the max number of pixels that the internal buffer can store in the provided format.
	size_t maxConvertedPixels(const PixelFormat& format);

	uint32_t convertValue(const PixelFormat& destFormat, const PixelFormat& sourceFormat, uint32_t sourceValue);

	// Converts the provided data from the source to destination format, if possible.
	// If the conversion was not possible, the returned blob will be invalid.
	// This function uses a fixed-length static memory buffer, so is not thread-safe.
	// In addition, depending on how much space the destination format requires, not
	// all of the source data may be converted. The length of the returned blob
	// should be checked against the destination pixel format byte depth to determine
	// how many pixels were converted.
	CoreUtil::ConstBlob convertPixelData(const PixelFormat& destFormat,
										 const ConstBitmapBuffer& sourceBuffer,
										 const ConstBitmapBuffer& palette = ConstBitmapBuffer());
}
