#include <BadgerGL/FontCharacterGroup.h>

namespace BadgerGL
{
	FontCharacterGroup::FontCharacterGroup(FontCharacterInfo* charInfoData,
										   size_t charInfoCount,
										   size_t codePointBase) :
		m_CharInfoData(charInfoData),
		m_CharInfoCount(charInfoCount),
		m_CodePointBase(codePointBase)
	{
	}

	FontCharacterInfo* FontCharacterGroup::charInfo(size_t codePoint)
	{
		if ( !m_CharInfoData || codePoint < m_CodePointBase || codePoint >= m_CodePointBase + m_CharInfoCount )
		{
			return nullptr;
		}

		return &m_CharInfoData[codePoint - m_CodePointBase];
	}

	const FontCharacterInfo* FontCharacterGroup::charInfo(size_t codePoint) const
	{
		if ( !m_CharInfoData || codePoint < m_CodePointBase || codePoint >= m_CodePointBase + m_CharInfoCount )
		{
			return nullptr;
		}

		return &m_CharInfoData[codePoint - m_CodePointBase];
	}

	FontCharacterGroup* FontCharacterGroup::nextGroup() const
	{
		return m_NextGroup;
	}

	void FontCharacterGroup::setNextGroup(FontCharacterGroup* next)
	{
		m_NextGroup = next;
	}

	size_t FontCharacterGroup::codePointMin() const
	{
		return m_CharInfoCount > 0 ? m_CodePointBase : 0;
	}

	size_t FontCharacterGroup::codePointMax() const
	{
		return m_CharInfoCount > 0 ? (m_CodePointBase + m_CharInfoCount - 1) : 0;
	}
}
