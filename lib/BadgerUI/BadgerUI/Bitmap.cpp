#include "Bitmap.h"

namespace BadgerUI
{
	Bitmap::Bitmap() :
		BaseUIDrawable()
	{
	}

	const BadgerGL::ConstBitmapSurface* Bitmap::bitmap() const
	{
		return m_Bitmap;
	}

	void Bitmap::setBitmap(const BadgerGL::ConstBitmapSurface* inBitmap)
	{
		setPropertyIfDifferent(m_Bitmap, inBitmap);
	}

	const Bitmap::SourceRect& Bitmap::sourceRect() const
	{
		return m_SourceRect;
	}

	void Bitmap::setSourceRect(const SourceRect& rect)
	{
		setPropertyIfDifferent(m_SourceRect, rect);
	}

	UIPoint Bitmap::position() const
	{
		return rect().min();
	}

	void Bitmap::setPosition(const UIPoint& pos)
	{
		setRectInternal(UIRect(pos, 0, 0));
	}

	void Bitmap::setOverrideDimensions(const UIDimensions& dim)
	{
		const UIPoint pos = position();
		setRectInternal(UIRect(pos, pos + dim.vector2DCast<UIPoint>()));
	}

	void Bitmap::delegatedDraw(const UIDrawContext& context)
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
