#pragma once

#include "BitmapMaskFont.h"
#include "BitmapMaskBlitter.h"

namespace BadgerGL
{
	class StringRenderer
	{
	public:
		const BitmapMaskFont* font() const;
		void setFont(const BitmapMaskFont* font);

		BitmapMaskBlitter* blitter() const;
		void setBlitter(BitmapMaskBlitter* bltr);

		void renderString(const char* str, const Rect16& destRect, int16_t xShift = 0);
		size_t calculateStringWidth(const char* str) const;

	private:
		void drawCharacter(const BitmapMaskFont::CharInfo& chInfo, const Rect16& destRect) const;

		const BitmapMaskFont* m_Font = nullptr;
		BitmapMaskBlitter* m_Blitter = nullptr;
	};
}
