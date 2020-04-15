#include "Image.h"

namespace BadgerUI
{
	Image::Image() :
		BaseUIDrawable()
	{
		setDrawCallback(&Image::privateDraw);
	}

	const UIPoint& Image::position() const
	{
		return m_Position;
	}

	void Image::setPosition(const UIPoint& pos)
	{
		setPropertyIfDifferent(m_Position, pos);
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

	void Image::privateDraw(const UIDrawContext& context)
	{
		if ( !m_Bitmap || !m_Bitmap->isValid() )
		{
			return;
		}

		context.renderer->blit(*m_Bitmap, m_Position, m_SourceRect);
	}
}
