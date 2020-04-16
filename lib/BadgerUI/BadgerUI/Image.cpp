#include "Image.h"

namespace BadgerUI
{
	Image::Image() :
		BaseUIDrawable()
	{
		setDrawCallback(&Image::privateDraw);
	}

	const BadgerGL::ConstBitmapSurface* Image::bitmap() const
	{
		return m_Bitmap;
	}

	void Image::setBitmap(const BadgerGL::ConstBitmapSurface* inBitmap)
	{
		setPropertyIfDifferent(m_Bitmap, inBitmap);
	}

	const Image::SourceRect& Image::sourceRect() const
	{
		return m_SourceRect;
	}

	void Image::setSourceRect(const SourceRect& rect)
	{
		setPropertyIfDifferent(m_SourceRect, rect);
	}

	UIPoint Image::position() const
	{
		return rect().min();
	}

	void Image::setPosition(const UIPoint& pos)
	{
		setRectInternal(UIRect(pos, 0, 0));
	}

	void Image::setOverrideDimensions(const UIDimensions& dim)
	{
		const UIPoint pos = position();
		setRectInternal(UIRect(pos, pos + dim.vector2DCast<UIPoint>()));
	}

	void Image::privateDraw(const UIDrawContext& context)
	{
		if ( !m_Bitmap || !m_Bitmap->isValid() )
		{
			return;
		}

		const UIRect& destRect = rect();

		if ( destRect.isNull() )
		{
			// Only use the top left point of the item's rect.
			context.renderer->blit(*m_Bitmap, destRect.min(), m_SourceRect);
		}
		else
		{
			// Use the entire rect.
			context.renderer->blit(*m_Bitmap, destRect, m_SourceRect);
		}
	}
}
