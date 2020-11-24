#pragma once

#include <StringLib/UTF8CharacterGroup.h>
#include <BadgerGL/FontCharacterGroup.h>

namespace BadgerGL
{
	// For a range of characters [BEGIN END]:
	template<StringLib::UTF8CharacterGroup GROUP, size_t BEGIN, size_t END>
	class StaticDataFontCharacterGroup : public FontCharacterGroup
	{
	public:
		static constexpr size_t NUM_CHARS = END - BEGIN + 1;
		static constexpr size_t BASE = static_cast<size_t>(GROUP) + BEGIN;

		inline StaticDataFontCharacterGroup() :
			FontCharacterGroup(m_Data, NUM_CHARS, BASE)
		{
			static_assert(END >= BEGIN, "Character range was not valid!");
		}

	private:
		FontCharacterInfo m_Data[NUM_CHARS];
	};
}
