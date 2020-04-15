#pragma once

#include "Image.h"
#include "Types.h"

namespace BadgerUI
{
	class TiledImage : public Image
	{
	public:
		TiledImage();

		const UIDimensions& dimensions() const;
		void setDimensions(const UIDimensions& dim);

	private:
		void privateDraw(const UIDrawContext& context);

		UIDimensions m_Dimensions;
	};
}
