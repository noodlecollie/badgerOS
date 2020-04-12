#pragma once

#include <BadgerGL/BitmapSurface.h>
#include <Resources/Images/Meta/StaticImageMetadata.h>

namespace ResourceLoaders
{
	BadgerGL::ConstBitmapSurface loadStaticBitmap(const Resources::StaticImageMetadata& meta);
}
