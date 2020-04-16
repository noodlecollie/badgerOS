#include "Box.h"

namespace BadgerUI
{
	Box::Box() :
		BaseUIDrawable()
	{
		setDrawCallback(&Box::privateDraw);
	}

	void Box::setRect(const UIRect& inRect)
	{
		setRectInternal(inRect);
	}

	BadgerGL::ShapeDrawStyle Box::drawStyle() const
	{
		return m_DrawStyle;
	}

	void Box::setDrawStyle(BadgerGL::ShapeDrawStyle style)
	{
		setPropertyIfDifferent(m_DrawStyle, style);
	}

	uint8_t Box::outlineWidth() const
	{
		return m_OutlineWidth;
	}

	void Box::setOutlineWidth(uint8_t width)
	{
		setPropertyIfDifferent(m_OutlineWidth, width);
	}

	const ColourProperty& Box::outlineColour() const
	{
		return m_OutlineColour;
	}

	void Box::setOutlineColour(const ColourProperty& col)
	{
		setPropertyIfDifferent(m_OutlineColour, col);
	}

	const ColourProperty& Box::fillColour() const
	{
		return m_FillColour;
	}

	void Box::setFillColour(const ColourProperty& col)
	{
		setPropertyIfDifferent(m_FillColour, col);
	}

	void Box::privateDraw(const UIDrawContext& context)
	{
		context.renderer->setLineWidth(m_OutlineWidth);
		context.renderer->setShapeDrawStyle(m_DrawStyle);

		if ( m_DrawStyle == BadgerGL::ShapeDrawStyle::Filled )
		{
			context.renderer->setPrimaryColour(m_FillColour.schemeColour(*context.colourScheme));
		}
		else
		{
			context.renderer->setPrimaryColour(m_OutlineColour.schemeColour(*context.colourScheme));
			context.renderer->setSecondaryColour(m_FillColour.schemeColour(*context.colourScheme));
		}

		context.renderer->draw(rect());
	}
}
