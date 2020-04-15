#include <CoreUtil/BgrsAssert.h>
#include "PixelFormatConverter_65K.h"
#include "../Defs.h"

namespace BadgerGL
{
	namespace PixelFormatConverter_65K
	{
		static bool canConvert(PixelFormatId id)
		{
			switch ( id )
			{
				case PixelFormat_0RGB:
				case PixelFormat_RGB0:
				case PixelFormat_65K:
				{
					return true;
				}

				default:
				{
					return false;
				}
			}
		}

		static bool convertValue(uint32_t& dest, uint32_t source, PixelFormatId destFormat)
		{
			switch ( destFormat )
			{
				case PixelFormat_0RGB:
				{
					dest = col24To16(source);
					break;
				}

				case PixelFormat_RGB0:
				{
					dest = col32To16(source);
					break;
				}

				case PixelFormat_65K:
				{
					dest = source;
					break;
				}

				default:
				{
					return false;
				}
			}

			return true;
		}

		static bool convertPixels(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer)
		{
			BGRS_ASSERT(false, "convertPixels is currently unimplemented.");
			return false;
		}

		static bool convertPixelsViaPalette(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer, const ConstBitmapBuffer& palette)
		{
			BGRS_ASSERT(false, "convertPixelsViaPalette is currently unimplemented.");
			return false;
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
