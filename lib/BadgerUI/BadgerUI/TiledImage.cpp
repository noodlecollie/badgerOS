#include "TiledImage.h"

namespace BadgerUI
{
	TiledImage::TiledImage() :
		Image()
	{
		setDrawCallback(&TiledImage::privateDraw);
	}

	const UIDimensions& TiledImage::dimensions() const
	{
		return m_Dimensions;
	}

	void TiledImage::setDimensions(const UIDimensions& dim)
	{
		setPropertyIfDifferent(m_Dimensions, dim);
	}

	void TiledImage::privateDraw(const UIDrawContext& context)
	{
		const BadgerGL::ConstBitmapSurface* bmp = bitmap();

		if ( !bmp )
		{
			return;
		}

		context.renderer->blit(*bmp, UIRect(position(), m_Dimensions.x(), m_Dimensions.y()), sourceRect());
	}
}
