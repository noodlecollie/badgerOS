#pragma once

#include <cstddef>
#include <BadgerGL/FontCharacterInfo.h>

namespace BadgerGL
{
	class FontCharacterGroup
	{
	public:
		FontCharacterGroup(FontCharacterInfo* charInfoData,
						   size_t charInfoCount,
						   size_t codePointBase);

		FontCharacterInfo* charInfo(size_t codePoint);
		const FontCharacterInfo* charInfo(size_t codePoint) const;

		FontCharacterGroup* nextGroup() const;

		size_t codePointMin() const;
		size_t codePointMax() const;

	private:
		friend class FontCharacterGroupContainer;

		void setNextGroup(FontCharacterGroup* next);

		FontCharacterInfo* m_CharInfoData = nullptr;
		size_t m_CharInfoCount = 0;
		size_t m_CodePointBase = 0;
		FontCharacterGroup* m_NextGroup = nullptr;
	};
}
