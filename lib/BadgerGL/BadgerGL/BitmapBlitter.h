#pragma once

#include "BitmapSurface.h"

namespace BadgerGL
{
	class BitmapBlitter
	{
		using SurfaceRect = BitmapSurface::SurfaceRect;
		using SurfaceVector = BitmapSurface::SurfaceVector;

	public:
		// If the rect is empty, the entire bitmap is used. Otherwise, the specified portion is used.
		void setSource(const ConstBitmapSurface* source, const SurfaceRect& rect = SurfaceRect());

		// If the rect is empty, its min is used as the destination position and the
		// specified area of the source bitmap is blitted once, without tiling.
		// If the rect is not empty, the specified area of the source bitmap is tiled
		// across the destination bitmap area.
		// Destination bitmaps that use palettes are not supported.
		void setDest(BitmapSurface* dest, const Rect16& rect);

		const SurfaceRect& sourceRect() const;
		const Rect16& destRect() const;

		bool blit();

	private:
		void chooseRects();
		void clipRects();
		void cacheWorkingVariables();
		void blitMatchingPixelFormats();
		void blitNonMatchingPixelFormats();

		const ConstBitmapSurface* m_Source = nullptr;
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
