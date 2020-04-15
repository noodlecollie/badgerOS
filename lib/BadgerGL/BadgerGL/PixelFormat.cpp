#include <CoreUtil/ArrayUtil.h>
#include "PixelFormat.h"

namespace BadgerGL
{
	static const PixelFormat* const PixelFormats[] =
	{
		&PIXELFORMAT_65K,
		&PIXELFORMAT_MONO256
	};

	const PixelFormat* getPixelFormat(PixelFormatId id)
	{
		for ( uint32_t index = 0; index < CoreUtil::arraySize(PixelFormats); ++index )
		{
			BGRS_ASSERT(PixelFormats[index], "Pixel format was not valid.");

			if ( PixelFormats[index]->id == id )
			{
				return PixelFormats[index];
			}
		}

		return nullptr;
	}
}
