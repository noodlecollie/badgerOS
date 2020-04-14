#include "PixelFormatConverters.h"

#include "PixelFormatConverterDelegations/PixelFormatConverter_65K.h"

namespace BadgerGL
{
	// This value is chosen so that it encompasses one full row of the SSD1351 OLED.
	// This optimises for blitting data into the OLED frame buffer, as the converted
	// data will then not have to be split up into chunks.
	static constexpr size_t MAX_CONVERTED_DATA_LENGTH = 128 * sizeof(uint16_t);

	static uint8_t ConvertedDataBuffer[MAX_CONVERTED_DATA_LENGTH];

	static const PixelFormatConverter* const FormatConverters[PixelFormat__Count] =
	{
		&PixelFormatConverter_65K::Converter,	// PixelFormat_65K
		nullptr									// PixelFormat_Mono256
	};

	const PixelFormatConverter* getPixelFormatConverter(PixelFormatId destType)
	{
		if ( destType >= PixelFormat__Count )
		{
			return nullptr;
		}

		const PixelFormatConverter* converter = FormatConverters[destType];

		if ( !converter || !converter->isValid(destType) )
		{
			return nullptr;
		}

		return converter;
	}

	size_t maxConvertedPixels(const PixelFormat& format)
	{
		return MAX_CONVERTED_DATA_LENGTH / format.totalByteDepth();
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
			converter->convertViaPalette(destBuffer, sourceBuffer, palette);
		}
		else
		{
			converter->convert(destBuffer, sourceBuffer);
		}

		return CoreUtil::ConstBlob(ConvertedDataBuffer, destBufferSize);
	}
}
