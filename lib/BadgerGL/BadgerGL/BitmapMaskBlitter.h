#pragma once

#include "BaseBlitter.h"
#include "BitmapMask.h"

namespace BadgerGL
{
	class BitmapMaskBlitter : public BaseBlitter
	{
	public:
		using SurfaceRect = BaseBlitter::SurfaceRect;
		using SurfaceVector = BaseBlitter::SurfaceVector;

		// If the rect is empty, the entire bitmap is used. Otherwise, the specified portion is used.
		void setSource(const BitmapMask* source, const SurfaceRect& rect = SurfaceRect());

		// Colours are assumed to be in the destination pixel format.
		void setPrimaryColour(uint32_t col);
		void setSecondaryColour(uint32_t col);
		void setDrawSecondaryColour(bool draw);

		bool blit();

	private:
		void blitInternal();

		const BitmapMask* m_Source = nullptr;
		uint32_t m_PrimaryColour = 0;
		uint32_t m_SecondaryColour = 0;
		bool m_DrawSecondaryColour = false;
	};
}
