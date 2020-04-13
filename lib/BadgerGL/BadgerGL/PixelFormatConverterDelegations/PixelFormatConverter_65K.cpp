#include <CoreUtil/BgrsAssert.h>
#include "PixelFormatConverter_65K.h"

namespace BadgerGL
{
	namespace PixelFormatConverter_65K
	{
		static bool canConvert(PixelFormatId id)
		{
			BGRS_ASSERT(false, "65K pixel format converter is currently unimplemented.");
			return false;
		}

		static bool convert(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer)
		{
			BGRS_ASSERT(false, "65K pixel format converter is currently unimplemented.");
			return false;
		}

		static bool convertViaPalette(BitmapBuffer& destBuffer, const ConstBitmapBuffer& sourceBuffer, const ConstBitmapBuffer& palette)
		{
			BGRS_ASSERT(false, "65K pixel format converter is currently unimplemented.");
			return false;
		}

		const PixelFormatConverter Converter =
		{
			.destType = PixelFormat_65K,
			.canConvert = &canConvert,
			.convert = &convert,
			.convertViaPalette = &convertViaPalette
		};
	}
}
