#pragma once

#include <CoreUtil/Blob.h>
#include <BadgerGL/FontCharacterGroupContainer.h>
#include <BadgerGL/BitmapMask.h>
#include <BadgerGL/BitmapMaskFont.h>

namespace BadgerUI
{
	namespace Fonts
	{
		class BaseFont : public BadgerGL::BitmapMaskFont
		{
		protected:
			void initialise();

			const BadgerGL::BitmapMask* m_FontBitmap = nullptr;
			CoreUtil::ConstBlob m_BMFData;
			BadgerGL::FontCharacterGroupContainer m_CharGroupContainer;
		};
	}
}
