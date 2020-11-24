#pragma once

#include <BadgerGL/BitmapMask.h>

namespace BadgerGL
{
	struct FontCharacterInfo
	{
		// Where the character's bitmap is located on the font bitmap.
		// If there is no bitmap (eg. for a space character), the rect
		// width/height should be 0 and the advance should specify
		// where to draw the next character.
		BitmapMask::SurfaceRect imageRect;

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
}
