#include <cstring>
#include <CoreUtil/BgrsAssert.h>
#include "PixelFormatConverter_65K.h"
#include "../Defs.h"

namespace BadgerGL
{
	namespace PixelFormatConverter_65K
	{
		using PixelConvertFunc = uint16_t (*)(uint32_t);
		using RawPixelConvertFunc = uint16_t (*)(const uint8_t*);

		static uint16_t convert0RGBto65K(const uint8_t* data)
		{
			// Skip the 0, since we only care about the RGB.
			const uint32_t value = data[0] | (data[1] << 8) | (data[2] << 16);
			return col24To16(value);
		}

		static uint16_t convertRGB0To65K(const uint8_t* data)
		{
			// Skip the 0, since we only care about the RGB.
			const uint32_t value = data[1] | (data[2] << 8) | (data[3] << 16);
			return col32To16(value);
		}

		static inline PixelConvertFunc conversionFunction(PixelFormatId sourceFormat)
		{
			switch ( sourceFormat )
			{
				case PixelFormat_0RGB:
				{
					return &col24To16;
				}

				case PixelFormat_RGB0:
				{
					return &col32To16;
				}

				default:
				{
					return nullptr;
				}
			}
		}

		static inline RawPixelConvertFunc rawConversionFunction(PixelFormatId sourceFormat)
		{
			switch ( sourceFormat )
			{
				case PixelFormat_0RGB:
				{
					return &convert0RGBto65K;
				}

				case PixelFormat_RGB0:
				{
					return &convertRGB0To65K;
				}

				default:
				{
					return nullptr;
				}
			}
		}

		static bool canConvert(PixelFormatId id)
		{
			return id == PixelFormat_65K || conversionFunction(id) != nullptr;
		}

		static bool convertValue(uint32_t& dest, uint32_t source, PixelFormatId sourceFormat)
		{
			if ( sourceFormat == PixelFormat_65K )
			{
				dest = source;
				return true;
			}

			const PixelConvertFunc convertFunc = conversionFunction(sourceFormat);

			if ( !convertFunc )
			{
				return false;
			}

			dest = convertFunc(source);
			return true;
		}

		static bool convertPixels(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer)
		{
			if ( *destBuffer.pixelFormat() == *sourceBuffer.pixelFormat() )
			{
				memcpy(destBuffer.rawData(), sourceBuffer.constRawData(), destBuffer.lengthInBytes());
				return true;
			}

			const RawPixelConvertFunc convertFunc = rawConversionFunction(sourceBuffer.pixelFormat()->id);

			if ( !convertFunc )
			{
				return false;
			}

			const size_t numPixelsToConvert = destBuffer.lengthInPixels();
			uint16_t* destPixelData = static_cast<uint16_t*>(destBuffer.rawData());
			uint16_t* const destPixelEnd = destPixelData + numPixelsToConvert;
			const uint8_t* sourcePixelData = static_cast<const uint8_t*>(sourceBuffer.constRawData());
			const size_t sourceByteDepth = sourceBuffer.pixelFormat()->totalByteDepth();

			while ( destPixelData < destPixelEnd )
			{
				*destPixelData = convertFunc(sourcePixelData);

				sourcePixelData += sourceByteDepth;
				++destPixelData;
			}

			return true;
		}

		static bool convertPixelsViaPalette(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer, const ConstBitmapBuffer& palette)
		{
			const bool sameFormat = destBuffer.pixelFormat()->id == palette.pixelFormat()->id;
			const PixelConvertFunc convertFunc = conversionFunction(sourceBuffer.pixelFormat()->id);

			if ( (!sameFormat && !convertFunc) || sourceBuffer.pixelFormat()->id != PixelFormat_Mono256 )
			{
				return false;
			}

			const size_t numPixelsToConvert = destBuffer.lengthInPixels();
			uint16_t* destPixelData = static_cast<uint16_t*>(destBuffer.rawData());
			uint16_t* const destPixelEnd = destPixelData + numPixelsToConvert;
			const uint8_t* sourcePixelData = sourceBuffer.constData<uint8_t>();
			const uint8_t* palettePixelData = static_cast<const uint8_t*>(palette.constRawData());
			const size_t paletteSize = palette.lengthInPixels();

			while ( destPixelData < destPixelEnd )
			{
				uint32_t pixel = 0;
				const uint8_t paletteLookup = *sourcePixelData;

				if ( paletteLookup < paletteSize )
				{
					pixel = palettePixelData[paletteLookup];
				}

				*destPixelData = sameFormat ? static_cast<uint16_t>(pixel) : convertFunc(pixel);

				++sourcePixelData;
				++destPixelData;
			}

			return true;
		}

		const PixelFormatConverter Converter =
		{
			.destType = PixelFormat_65K,
			.canConvert = &canConvert,
			.convertValue = &convertValue,
			.convertPixels = &convertPixels,
			.convertPixelsViaPalette = &convertPixelsViaPalette
		};
	}
}
