#include "PixelFormat.h"

namespace BadgerGL
{
	static const PixelFormat* const PixelFormats[PixelFormat__Count] =
	{
		&PIXELFORMAT_65K,		// PixelFormat_65K
		&PIXELFORMAT_MONO256	// PixelFormat_Mono256
	};

	const PixelFormat* getPixelFormat(PixelFormatId id)
	{
		if ( id >= 0 && id < PixelFormat__Count )
		{
			return PixelFormats[id];
		}
		else
		{
			return nullptr;
		}
	}
}
