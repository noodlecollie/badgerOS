#pragma once

#include <BadgerGL/Defs.h>
#include "BaseUIDrawable.h"
#include "Types.h"
#include "ColourScheme.h"

namespace BadgerUI
{
	class Box : public BaseUIDrawable
	{
	public:
		Box();

		const UIRect& rect() const;
		void setRect(const UIRect& inRect);

		BadgerGL::ShapeDrawStyle drawStyle() const;
		void setDrawStyle(BadgerGL::ShapeDrawStyle style);

		uint8_t outlineWidth() const;
		void setOutlineWidth(uint8_t width);

		const ColourProperty& outlineColour() const;
		void setOutlineColour(const ColourProperty& col);

		const ColourProperty& fillColour() const;
		void setFillColour(const ColourProperty& col);

	private:
		void privateDraw(const UIDrawContext& context);

		UIRect m_Rect;
		BadgerGL::ShapeDrawStyle m_DrawStyle = BadgerGL::ShapeDrawStyle::Filled;
		uint8_t m_OutlineWidth = 1;
		ColourProperty m_OutlineColour;
		ColourProperty m_FillColour;
	};
}
