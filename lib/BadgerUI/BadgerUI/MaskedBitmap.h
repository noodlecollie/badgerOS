#pragma once

#include "BaseUIDrawable.h"
#include "ColourScheme.h"

namespace BadgerUI
{
	class MaskedBitmap : public BaseUIDrawable
	{
	public:
		using SourceRect = BadgerGL::ConstBitmapSurface::SurfaceRect;

		MaskedBitmap();

		const BadgerGL::BitmapMask* bitmap() const;
		void setBitmap(const BadgerGL::BitmapMask* inBitmap);

		const SourceRect& sourceRect() const;
		void setSourceRect(const SourceRect& rect);

		// Not a reference because this is computed from the bounds.
		UIPoint position() const;
		void setPosition(const UIPoint& pos);

		// If set, specifies the target rect size, tiling the source image
		// across this area if it is smaller than the area.
		// If override dimensions are not set, the entire source image
		// specified by the source rect is drawn.
		// Setting dimensions of 0 clears the override dimensions.
		void setOverrideDimensions(const UIDimensions& dim);

		const ColourProperty& primaryColour() const;
		void setPrimaryColour(const ColourProperty& colour);

		const ColourProperty& secondaryColour() const;
		void setSecondaryColour(const ColourProperty& colour);

		bool drawSecondaryColour() const;
		void setDrawSecondaryColour(bool draw);

	private:
		void privateDraw(const UIDrawContext& context);

		const BadgerGL::BitmapMask* m_Bitmap = nullptr;
		SourceRect m_SourceRect;
		ColourProperty m_PrimaryColour;
		ColourProperty m_SecondaryColour;
		bool m_DrawSecondaryColour = false;
	};
}
