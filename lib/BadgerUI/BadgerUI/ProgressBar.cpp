#include "ProgressBar.h"

namespace BadgerUI
{
	void ProgressBar::setRect(const UIRect& inRect)
	{
		m_Background.setDrawStyle(BadgerGL::ShapeDrawStyle::FilledOutline);
		m_Foreground.setDrawStyle(BadgerGL::ShapeDrawStyle::Filled);

		setRectInternal(inRect);
		updateBoxRects();
	}

	uint8_t ProgressBar::outlineWidth() const
	{
		return m_Background.outlineWidth();
	}

	void ProgressBar::setOutlineWidth(uint8_t width)
	{
		if ( width == m_Background.outlineWidth() )
		{
			return;
		}

		m_Background.setOutlineWidth(width);
		updateBoxRects();
	}

	const ColourProperty& ProgressBar::outlineColour() const
	{
		return m_Background.outlineColour();
	}

	void ProgressBar::setOutlineColour(const ColourProperty& col)
	{
		m_Background.setOutlineColour(col);
	}

	const ColourProperty& ProgressBar::backgroundColour() const
	{
		return m_Background.fillColour();
	}

	void ProgressBar::setBackgroundColour(const ColourProperty& col)
	{
		m_Background.setFillColour(col);
	}

	const ColourProperty& ProgressBar::foregroundColour() const
	{
		return m_Foreground.fillColour();
	}

	void ProgressBar::setForegroundColour(const ColourProperty& col)
	{
		m_Foreground.setFillColour(col);
	}

	float ProgressBar::filledFraction() const
	{
		return m_FilledFraction;
	}

	void ProgressBar::setFilledFraction(float frac)
	{
		if ( frac < 0.0f )
		{
			frac = 0.0f;
		}
		else if ( frac > 1.0f )
		{
			frac = 1.0f;
		}

		if ( frac == m_FilledFraction )
		{
			return;
		}

		m_FilledFraction = frac;
		m_FilledWidth = static_cast<size_t>(interiorWidth() * m_FilledFraction);
	}

	void ProgressBar::delegatedUpdate(const UIUpdateContext& context)
	{
		UIRect foregroundRect = m_Foreground.rect();
		const size_t foregroundWidth = foregroundRect.width();

		if ( foregroundWidth == m_FilledWidth )
		{
			return;
		}

		foregroundRect.ensureMinMaxOrdered();

		UIPoint p1 = foregroundRect.p1();
		p1.setX(foregroundRect.p0().x() + m_FilledWidth);

		m_Foreground.setRect(UIRect(foregroundRect.p0(), p1));

		m_Background.update(context);
		m_Foreground.update(context);

		setDirtyStateInternal(std::max(m_Background.dirtyState(), m_Foreground.dirtyState()));
	}

	void ProgressBar::delegatedDraw(const UIDrawContext& context)
	{
		m_Background.draw(context);
		m_Foreground.draw(context);
	}

	void ProgressBar::updateBoxRects()
	{
		UIRect tempRect(rect());
		m_Background.setRect(tempRect);

		const uint8_t outline = m_Background.outlineWidth();
		tempRect.expand(static_cast<UIPoint::ValueType>(outline) * -1);
		m_Foreground.setRect(tempRect);
	}

	float ProgressBar::interiorWidth() const
	{
		size_t width = m_Background.rect().width();
		const size_t reduction = 2 * static_cast<size_t>(m_Background.outlineWidth());

		return reduction < width
			? static_cast<float>(width - reduction)
			: 0.0f;
	}
}
