#pragma once

#include <BadgerMath/Rect2D.h>
#include "BitmapSurface.h"
#include "BitmapMask.h"
#include "Defs.h"
#include "BitmapMaskFont.h"
#include "Patterns.h"

namespace BadgerGL
{
	class BitmapBlitter;
	class BitmapMaskBlitter;

	// Class for rendering graphics to a provided bitmap.
	// The bitmap is expected to exist for the lifetime of the class instance.
	// Rendering to bitmaps which use palettes is not supported right now,
	// and will yield undefined behaviour.
	// This class is not thread-safe.
	class BitmapRenderer
	{
	public:
		explicit BitmapRenderer(BitmapSurface* surface = nullptr);

		BitmapSurface* bitmap() const;
		void setBitmap(BitmapSurface* bitmap);
		bool hasBitmap() const;

		const URect16& dirtyArea() const;

		ShapeDrawStyle shapeDrawStyle() const;
		void setShapeDrawStyle(ShapeDrawStyle style);

		uint32_t primaryColour() const;
		void setPrimaryColour(uint32_t col);

		uint32_t secondaryColour() const;
		void setSecondaryColour(uint32_t col);

		uint8_t lineWidth() const;
		void setLineWidth(uint8_t width);

		uint8_t bitGradientType() const;
		void setBitGradientType(uint8_t type);

		PatternDirection bitGradientDirection() const;
		void setBitGradientDirection(PatternDirection direction);

		const BitmapMaskFont* font() const;
		void setFont(const BitmapMaskFont* fnt);

		// Used to offset the position of anything being drawn.
		// Useful for "instancing" primitives by drawing the same
		// input primitive data each time in different locations.
		Point16 drawingOffset() const;
		void setDrawingOffset(const Point16& offset);
		void resetDrawingOffset();

		void draw(const Rect16& rect);
		void drawPatterned(const Rect16& rect);

		void fillWithPrimaryColour();
		void fillWithSecondaryColour();

		// Tiles the given bitmap over the area specified by destRect.
		// If sourceRect is not null, it defines the portion of the source bitmap that will be used.
		// Otherwise, the entire bitmap will be used.
		// If destRect is empty, its min is used as the origin of the blitted bitmap, and the area
		// that is filled is equal to the source rect.
		// This function supports source bitmaps that use palettes.
		void blit(const ConstBitmapSurface& source,
				  const Rect16& destRect,
				  const BitmapSurface::SurfaceRect& sourceRect = BitmapSurface::SurfaceRect());

		// Same as above, but the dest rect dimensions are taken from the source rect.
		inline void blit(const ConstBitmapSurface& source,
						 const Point16& destPos,
						 const BitmapSurface::SurfaceRect& sourceRect = BitmapSurface::SurfaceRect())
		{
			blit(source, Rect16(destPos, 0, 0), sourceRect);
		}

		// Same as blit(), but uses a bitmap mask. Draws in the primary colour.
		void blitMask(const BitmapMask& source,
					  const Rect16& destRect,
					  const BitmapMask::SurfaceRect& sourceRect = BitmapMask::SurfaceRect(),
					  bool drawSecondaryColour = false);

		// Same as above, but the dest rect dimensions are taken from the source rect.
		inline void blitMask(const BitmapMask& source,
							 const Point16& destPos,
							 const BitmapMask::SurfaceRect& sourceRect = BitmapMask::SurfaceRect(),
							 bool drawSecondaryColour = false)
		{
			blitMask(source, Rect16(destPos, 0, 0), sourceRect, drawSecondaryColour);
		}

		void drawString(const char* string, const Rect16& destRect, const Point16& adjustment = Point16());

	private:
		void fill(uint32_t colour);
		void drawOutline(const Rect16& rect);
		void drawFilled(const Rect16& rect, uint32_t colour);
		void addToDirtyArea(const URect16& area);
		void addToDirtyArea(const BitmapBlitter& blitter);
		void addToDirtyArea(const BitmapMaskBlitter& blitter);

		BitmapSurface* m_Surface = nullptr;
		URect16 m_DirtyArea;
		ShapeDrawStyle m_ShapeDrawStyle = ShapeDrawStyle::Outline;
		uint32_t m_PrimaryColour = 0xFFFFFFFF;
		uint32_t m_SecondaryColour = 0x00000000;
		uint8_t m_LineWidth = 1;
		PatternDirection m_PatternDirection = PatternDirection::Horizontal;
		uint8_t m_BitGradientType = 4;
		Point16 m_DrawingOffset;
		const BitmapMaskFont* m_Font = nullptr;
	};
}
