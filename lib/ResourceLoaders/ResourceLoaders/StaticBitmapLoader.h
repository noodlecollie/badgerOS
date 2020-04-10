#pragma once

#include <BadgerGL/BitmapSurface.h>
#include <Resources/Images/Meta/StaticImageMetadata.h>

namespace ResourceLoaders
{
	void loadStaticBitmap(BadgerGL::BitmapSurface& bitmap, const Resources::StaticImageMetadata& meta);
}
