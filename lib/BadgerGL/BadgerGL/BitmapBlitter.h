#pragma once

#include "BaseBlitter.h"

namespace BadgerGL
{
	class BitmapBlitter : public BaseBlitter
	{
	public:
		using SurfaceRect = BaseBlitter::SurfaceRect;
		using SurfaceVector = BaseBlitter::SurfaceVector;

		// If the rect is empty, the entire bitmap is used. Otherwise, the specified portion is used.
		void setSource(const ConstBitmapSurface* source, const SurfaceRect& rect = SurfaceRect());

		bool blit();

	private:
		void blitMatchingPixelFormats();
		void blitMatchingPixelFormatsWithPalette();
		void blitNonMatchingPixelFormats();

		const ConstBitmapSurface* m_Source = nullptr;
	};
}
