#pragma once

#include <BadgerMath/Rect2D.h>
#include "BitmapSurface.h"
#include "Defs.h"

namespace BadgerGL
{
	class BitmapRenderer
	{
	public:
		explicit BitmapRenderer(BitmapSurface& surface);

		ShapeDrawStyle shapeDrawStyle() const;
		void setShapeDrawStyle(ShapeDrawStyle style);

		uint32_t primaryColour() const;
		void setPrimaryColour(uint32_t col);

		uint32_t secondaryColour() const;
		void setSecondaryColour(uint32_t col);

		uint8_t lineWidth() const;
		void setLineWidth(uint8_t width);

		void draw(const Rect16& rect);

	private:
		void drawOutline(const Rect16& rect);
		void drawFilled(const Rect16& rect, uint32_t colour);

		BitmapSurface* m_Surface = nullptr;
		Rect16 m_DirtyArea;
		ShapeDrawStyle m_ShapeDrawStyle = ShapeDrawStyle::Outline;
		uint32_t m_PrimaryColour = 0xFFFFFFFF;
		uint32_t m_SecondaryColour = 0x00000000;
		uint8_t m_LineWidth = 1;
	};
}
