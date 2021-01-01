#pragma once

#include <CoreUtil/Blob.h>
#include <BadgerGL/FontCharacterGroupContainer.h>
#include <BadgerGL/BitmapMask.h>
#include <BadgerGL/BitmapMaskFont.h>

namespace BadgerUI
{
	class BaseFontData : public BadgerGL::FontCharacterGroupContainer
	{
	public:
		bool isValid() const;

		const BadgerGL::BitmapMask* fontBitmap() const;
		const CoreUtil::ConstBlob& bmfData() const;
		const BadgerGL::BitmapMaskFont& fontObject() const;

		bool initialise();

	protected:
		void setFontBitmap(const BadgerGL::BitmapMask* bitmap);
		void setBMFData(const CoreUtil::ConstBlob& data);

	private:
		const BadgerGL::BitmapMask* m_FontBitmap = nullptr;
		CoreUtil::ConstBlob m_BMFData;
		BadgerGL::BitmapMaskFont m_FontObject;
	};

	template<typename T>
	class StaticFontData
	{
	public:
		static inline T& staticInstance()
		{
			static T instance;
			return instance;
		}
	};
}
