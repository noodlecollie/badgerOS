#pragma once

#include <BadgerGL/BitmapSurface.h>
#include "BaseUIDrawable.h"
#include "Types.h"

namespace BadgerUI
{
	class Image : public BaseUIDrawable
	{
	public:
		using SourceRect = BadgerGL::ConstBitmapSurface::SurfaceRect;

		Image();

		const BadgerGL::ConstBitmapSurface* bitmap() const;
		void setBitmap(const BadgerGL::ConstBitmapSurface* inBitmap);

		const SourceRect& sourceRect() const;
		void setSourceRect(const SourceRect& rect);

		// Not a reference because this is computed from the bounds.
		UIPoint position() const;
		void setPosition(const UIPoint& pos);

		// If set, specifies the target rect size, tiling the source image
		// across this area if it is smaller than the area.
		// If override dimensions are not set, the entire source image
		// specified by the source rect is drawn.
		// Setting dimensions of 0 clears the override dimensions.
		void setOverrideDimensions(const UIDimensions& dim);

	private:
		void privateDraw(const UIDrawContext& context);

		const BadgerGL::ConstBitmapSurface* m_Bitmap;
		SourceRect m_SourceRect;
	};
}
