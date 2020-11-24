#pragma once

#include <BadgerGL/FontCharacterGroup.h>

namespace BadgerGL
{
	class FontCharacterGroupContainer
	{
	public:
		FontCharacterInfo* charInfo(size_t codePoint);
		const FontCharacterInfo* charInfo(size_t codePoint) const;

		FontCharacterInfo* invalidGlyphInfo();
		const FontCharacterInfo* invalidGlyphInfo() const;

	protected:
		void addGroup(FontCharacterGroup* group);

	private:
		FontCharacterInfo* m_InvalidGlyph = nullptr;
		FontCharacterGroup* m_FirstGroup = nullptr;
		FontCharacterGroup* m_LastGroup = nullptr;
	};
}
