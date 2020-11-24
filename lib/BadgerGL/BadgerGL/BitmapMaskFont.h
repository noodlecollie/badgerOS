#pragma once

#include <cstdint>
#include <CoreUtil/DataBuffer.h>
#include <BadgerGL/BitmapMask.h>
#include <BadgerGL/FontCharacterGroupContainer.h>

namespace BadgerGL
{
	class BitmapMaskFont
	{
	public:
		BitmapMaskFont(const BitmapMask* fontBitmap = nullptr, const FontCharacterGroupContainer* charContainer = nullptr);

		const BitmapMask* fontBitmap() const;
		void setFontBitmap(const BitmapMask* bitmap);

		uint16_t lineHeight() const;
		void setLineHeight(uint16_t height);

		const FontCharacterGroupContainer* charContainer() const;
		void setCharContainer(const FontCharacterGroupContainer* charContainer);

		bool isValid() const;

		const FontCharacterInfo* characterInfo(size_t index) const;

		// For getting the character info for the first character of this string.
		// This should allow us to return the correct char info for multi-byte
		// UTF-8 characters in future - hence the argument is a const char* rather
		// than simply a char.
		const FontCharacterInfo* characterInfo(const char* stringPtr) const;

	private:
		const BitmapMask* m_FontBitmap = nullptr;
		const FontCharacterGroupContainer* m_CharContainer = nullptr;
		uint16_t m_LineHeight = 0;
	};
}
