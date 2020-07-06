#include "MaskedBitmap.h"

namespace BadgerUI
{
	MaskedBitmap::MaskedBitmap() :
		BaseUIDrawable()
	{
	}

	const BadgerGL::BitmapMask* MaskedBitmap::bitmap() const
	{
		return m_Bitmap;
	}

	void MaskedBitmap::setBitmap(const BadgerGL::BitmapMask* inBitmap)
	{
		setPropertyIfDifferent(m_Bitmap, inBitmap);
	}

	const MaskedBitmap::SourceRect& MaskedBitmap::sourceRect() const
	{
		return m_SourceRect;
	}

	void MaskedBitmap::setSourceRect(const SourceRect& rect)
	{
		setPropertyIfDifferent(m_SourceRect, rect);
	}

	UIPoint MaskedBitmap::position() const
	{
		return rect().min();
	}

	void MaskedBitmap::setPosition(const UIPoint& pos)
	{
		setRectInternal(UIRect(pos, 0, 0));
	}

	void MaskedBitmap::setOverrideDimensions(const UIDimensions& dim)
	{
		const UIPoint pos = position();
		setRectInternal(UIRect(pos, pos + dim.vector2DCast<UIPoint>()));
	}

	const ColourProperty& MaskedBitmap::primaryColour() const
	{
		return m_PrimaryColour;
	}

	void MaskedBitmap::setPrimaryColour(const ColourProperty& colour)
	{
		setPropertyIfDifferent(m_PrimaryColour, colour);
	}

	const ColourProperty& MaskedBitmap::secondaryColour() const
	{
		return m_SecondaryColour;
	}

	void MaskedBitmap::setSecondaryColour(const ColourProperty& colour)
	{
		setPropertyIfDifferent(m_SecondaryColour, colour);
	}

	bool MaskedBitmap::drawSecondaryColour() const
	{
		return m_DrawSecondaryColour;
	}

	void MaskedBitmap::setDrawSecondaryColour(bool draw)
	{
		setPropertyIfDifferent(m_DrawSecondaryColour, draw);
	}

	void MaskedBitmap::delegatedDraw(const UIDrawContext& context)
	{
		if ( !m_Bitmap || !m_Bitmap->isValid() )
		{
			return;
		}

		context.renderer->setPrimaryColour(m_PrimaryColour.schemeColour(*context.colourScheme));
		context.renderer->setSecondaryColour(m_SecondaryColour.schemeColour(*context.colourScheme));

		const UIRect& destRect = rect();

		if ( destRect.isNull() )
		{
			// Only use the top left point of the item's rect.
			context.renderer->blitMask(*m_Bitmap, destRect.min(), m_SourceRect, m_DrawSecondaryColour);
		}
		else
		{
			// Use the entire rect.
			context.renderer->blitMask(*m_Bitmap, destRect, m_SourceRect, m_DrawSecondaryColour);
		}
	}
}
