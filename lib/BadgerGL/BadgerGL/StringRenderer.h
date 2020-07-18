#pragma once

#include "BitmapMaskFont.h"
#include "BitmapMaskBlitter.h"

namespace BadgerGL
{
	class StringRenderer
	{
	public:
		static size_t calculateStringWidth(const BitmapMaskFont* font, const char* str);

		const BitmapMaskFont* font() const;
		void setFont(const BitmapMaskFont* font);

		BitmapMaskBlitter* blitter() const;
		void setBlitter(BitmapMaskBlitter* bltr);

		bool renderString(const char* str, const Rect16& destRect, int16_t xShift = 0);
		size_t calculateStringWidth(const char* str) const;

	private:
		void drawCharacter(const BitmapMaskFont::CharInfo& chInfo, const Rect16& destRect) const;

		const BitmapMaskFont* m_Font = nullptr;
		BitmapMaskBlitter* m_Blitter = nullptr;
	};
}
