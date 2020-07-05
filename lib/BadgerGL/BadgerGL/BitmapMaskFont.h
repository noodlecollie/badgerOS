#pragma once

#include <cstdint>
#include <CoreUtil/DataBuffer.h>
#include "BitmapMask.h"

namespace BadgerGL
{
	class BitmapMaskFont
	{
	public:
		struct CharInfo;

		using SurfaceRect = BitmapMask::SurfaceRect;
		using CharInfoBuffer = CoreUtil::DataBuffer<CharInfo>;

		struct CharInfo
		{
			// Where the character's bitmap is located on the font bitmap.
			// If there is no bitmap (eg. for a space character), the rect
			// width/height should be 0 and the advance should specify
			// where to draw the next character.
			SurfaceRect imageRect;

			// X and Y offset to shift the character image by when drawing it.
			Point16 drawOffset;

			// How many pixels to advance once the character has been drawn.
			// This is measured from the current cursor position, not from the
			// right hand side of the bitmap, so that consecutive character
			// bitmaps may be drawn overlapping each other if required.
			uint8_t advance;

			inline bool hasImage() const
			{
				return !imageRect.isEmpty();
			}
		};

		BitmapMaskFont(const BitmapMask* fontBitmap, const CharInfoBuffer& charDataBuffer);

		const BitmapMask* fontBitmap() const;
		bool isValid() const;
		size_t charCount() const;

		CharInfo* charData(size_t index);
		const CharInfo* charData(size_t index) const;

		// For getting the character info for the first character of this string.
		// This should allow us to return the correct char info for multi-byte
		// UTF-8 characters in future - hence the argument is a const char* rather
		// than simply a char.
		CharInfo* charData(const char* stringPtr);
		const CharInfo* charData(const char* stringPtr) const;

	private:
		const BitmapMask* m_FontBitmap = nullptr;
		CharInfoBuffer m_CharData;
	};
}
