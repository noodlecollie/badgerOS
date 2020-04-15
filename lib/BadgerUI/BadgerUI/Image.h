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

		const UIPoint& position() const;
		void setPosition(const UIPoint& pos);

		const BadgerGL::ConstBitmapSurface* bitmap() const;
		void setBitmap(const BadgerGL::ConstBitmapSurface* inBitmap);

		const SourceRect& sourceRect() const;
		void setSourceRect(const SourceRect& rect);

	private:
		void privateDraw(const UIDrawContext& context);

		UIPoint m_Position;
		const BadgerGL::ConstBitmapSurface* m_Bitmap;
		SourceRect m_SourceRect;
	};
}
