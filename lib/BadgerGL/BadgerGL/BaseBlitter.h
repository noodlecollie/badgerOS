#pragma once

#include "BitmapSurface.h"

namespace BadgerGL
{
	class BaseBlitter
	{
	public:
		using SurfaceRect = BitmapSurface::SurfaceRect;
		using SurfaceVector = BitmapSurface::SurfaceVector;

		const SurfaceRect& sourceRect() const;

		// If the rect is empty, the entire bitmap is used. Otherwise, the specified portion is used.
		void setSourceRect(const SurfaceRect& rect = SurfaceRect());

		const Rect16& destRect() const;

		// Same rules as setDest() for the rect.
		void setDestRect(const Rect16& rect);

		BitmapSurface* destBitmap() const;
		void setDestBitmap(BitmapSurface* bitmap);

		// If the rect is empty, its min is used as the destination position and the
		// specified area of the source bitmap is blitted once, without tiling.
		// If the rect is not empty, the specified area of the source bitmap is tiled
		// across the destination bitmap area.
		// Destination bitmaps that use palettes are not supported.
		void setDest(BitmapSurface* dest, const Rect16& rect);

	protected:
		void chooseRects(const SurfaceRect& sourceBounds);
		void clipRects(const SurfaceRect& sourceBounds);

		BitmapSurface* m_Dest = nullptr;
		SurfaceRect m_SourceRect;
		Rect16 m_DestRect;

		// If the min point of the destination rect was adjusted to fit within the bounds of the destination bitmap,
		// the first time we read from the source bitmap we must also adjust where we read from.
		// If we subsequently tile, we must begin again from the source rect min on whatever the tiling axis is.
		// This vector holds the initial offset that we use on the first iteration.
		SurfaceVector m_InitialSourceOffset;
	};
}
