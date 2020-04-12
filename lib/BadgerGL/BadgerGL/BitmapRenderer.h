#pragma once

#include <BadgerMath/Rect2D.h>
#include "BitmapSurface.h"
#include "Defs.h"

namespace BadgerGL
{
	// Class for rendering graphics to a provided bitmap.
	// The bitmap is expected to exist for the lifetime of the class instance.
	// Rendering to bitmaps which use palettes is not supported right now,
	// and will yield undefined behaviour.
	// This class is not thread-safe.
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

		// If sourceRect is not null, it defines the portion of the source bitmap that will be blitted.
		// This function supports source bitmaps that use palettes.
		void blit(const ConstBitmapSurface& source,
				  const Point16& pos,
				  const BitmapSurface::SurfaceRect& sourceRect = BitmapSurface::SurfaceRect());

	private:
		void drawOutline(const Rect16& rect);
		void drawFilled(const Rect16& rect, uint32_t colour);

		// Assumes that the source rect has been adjusted to remain inside the surface bounds.
		void blitInternal(const ConstBitmapSurface& source,
						  const ConstBitmapSurface::SurfaceVector& pos,
						  const ConstBitmapSurface::SurfaceRect& sourceRect);

		BitmapSurface* m_Surface = nullptr;
		Rect16 m_DirtyArea;
		ShapeDrawStyle m_ShapeDrawStyle = ShapeDrawStyle::Outline;
		uint32_t m_PrimaryColour = 0xFFFFFFFF;
		uint32_t m_SecondaryColour = 0x00000000;
		uint8_t m_LineWidth = 1;
	};
}
