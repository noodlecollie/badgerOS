#include <CoreUtil/BgrsAssert.h>
#include "StaticBitmapLoader.h"

namespace ResourceLoaders
{
	BadgerGL::ConstBitmapSurface loadStaticBitmap(const Resources::StaticImageMetadata& meta)
	{
		using namespace BadgerGL;
		using ConstBitmapInitialiser = ConstBitmapSurface::ConstBitmapInitialiser;

		BGRS_ASSERTD(meta.width > 0, "Resource width was zero.");
		BGRS_ASSERTD(meta.width <= std::numeric_limits<uint16_t>::max(), "Resource width exceeded max width.");
		BGRS_ASSERTD(meta.height > 0, "Resource height was zero.");
		BGRS_ASSERTD(meta.height <= std::numeric_limits<uint16_t>::max(), "Resource height exceeded max width.");
		BGRS_ASSERTD(meta.bitDepth > 0, "Resource bit depth was zero.");
		BGRS_ASSERTD(meta.bitDepth <= BadgerGL::BitmapSurface::MAX_BIT_DEPTH, "Resource bit depth exceeded max depth.");
		BGRS_ASSERTD(meta.isRowMajor, "Column-major static resources are not supported.");
		BGRS_ASSERTD(meta.data, "Resource data was null.");

		// FIXME: We need a way to handle const images!!
		//bitmap.setBitmap(meta.width, meta.height, (void*)meta.data, meta.bitDepth);
		return ConstBitmapSurface(ConstBitmapInitialiser(meta.width, meta.height, meta.bitDepth, meta.data));
	}
}
