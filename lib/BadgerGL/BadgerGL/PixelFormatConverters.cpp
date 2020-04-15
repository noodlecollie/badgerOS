#include <CoreUtil/ArrayUtil.h>
#include "PixelFormatConverters.h"

#include "PixelFormatConverterDelegations/PixelFormatConverter_65K.h"

namespace BadgerGL
{
	// This value is chosen so that it encompasses one full row of the SSD1351 OLED.
	// This optimises for blitting data into the OLED frame buffer, as the converted
	// data will then not have to be split up into chunks.
	static constexpr size_t MAX_CONVERTED_DATA_LENGTH = 128 * sizeof(uint16_t);

	static uint8_t ConvertedDataBuffer[MAX_CONVERTED_DATA_LENGTH];

	static const PixelFormatConverter* const FormatConverters[] =
	{
		&PixelFormatConverter_65K::Converter
	};

	const PixelFormatConverter* getPixelFormatConverter(PixelFormatId destType)
	{
		const PixelFormatConverter* converter = nullptr;

		for ( uint32_t index = 0; index < CoreUtil::arraySize(FormatConverters); ++index )
		{
			BGRS_ASSERT(FormatConverters[index], "Pixel format converter pointer was not valid.");

			if ( FormatConverters[index]->destType == destType )
			{
				converter = FormatConverters[index];
				break;
			}
		}

		if ( !converter->isValid(destType) )
		{
			BGRS_ASSERTD(false, "Pixel format converter was not valid.");
			return nullptr;
		}

		return converter;
	}

	size_t maxConvertedPixels(const PixelFormat& format)
	{
		return MAX_CONVERTED_DATA_LENGTH / format.totalByteDepth();
	}

	uint32_t convertValue(const PixelFormat& destFormat, const PixelFormat& sourceFormat, uint32_t sourceValue)
	{
		const PixelFormatConverter* converter = getPixelFormatConverter(destFormat.id);

		if ( !converter || !converter->canConvert(sourceFormat.id) )
		{
			return 0;
		}

		uint32_t out = 0;
		converter->convertValue(out, sourceValue, destFormat.id);

		return out;
	}

	CoreUtil::ConstBlob convertPixelData(const PixelFormat& destFormat,
										 const ConstBitmapBuffer& sourceBuffer,
										 const ConstBitmapBuffer& palette)
	{
		if ( !sourceBuffer.isValid() || (palette.isValid() && sourceBuffer.pixelFormat()->id != PixelFormat_Mono256) )
		{
			return CoreUtil::ConstBlob();
		}

		const PixelFormatConverter* converter = getPixelFormatConverter(destFormat.id);

		if ( !converter )
		{
			return CoreUtil::ConstBlob();
		}

		const PixelFormatId targetFormat = palette.isValid() ? palette.pixelFormat()->id : sourceBuffer.pixelFormat()->id;

		if ( !converter->canConvert(targetFormat) )
		{
			return CoreUtil::ConstBlob();
		}

		const size_t maxPixelsInTargetFormat = MAX_CONVERTED_DATA_LENGTH / destFormat.totalByteDepth();
		const size_t sourcePixelsToConvert = std::min(sourceBuffer.lengthInPixels(), maxPixelsInTargetFormat);
		const size_t destBufferSize = sourcePixelsToConvert * destFormat.totalByteDepth();

		BitmapBuffer destBuffer(ConvertedDataBuffer, destBufferSize, &destFormat);

		if ( palette.isValid() )
		{
			converter->convertPixelsViaPalette(destBuffer, sourceBuffer, palette);
		}
		else
		{
			converter->convertPixels(destBuffer, sourceBuffer);
		}

		return CoreUtil::ConstBlob(ConvertedDataBuffer, destBufferSize);
	}
}
