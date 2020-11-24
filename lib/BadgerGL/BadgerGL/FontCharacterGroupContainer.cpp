#include <CoreUtil/BgrsAssert.h>
#include <BadgerGL/FontCharacterGroupContainer.h>

namespace BadgerGL
{
	FontCharacterInfo* FontCharacterGroupContainer::charInfo(size_t codePoint)
	{
		for ( FontCharacterGroup* group = m_FirstGroup; group; group = group->nextGroup() )
		{
			if ( group->codePointMin() > codePoint )
			{
				// No point searching further for this character.
				break;
			}

			if ( group->codePointMax() < codePoint )
			{
				// Character group does not encompass this code point.
				continue;
			}

			return group->charInfo(codePoint);
		}

		return nullptr;
	}

	const FontCharacterInfo* FontCharacterGroupContainer::charInfo(size_t codePoint) const
	{
		for ( const FontCharacterGroup* group = m_FirstGroup; group; group = group->nextGroup() )
		{
			if ( group->codePointMin() > codePoint )
			{
				// No point searching further for this character.
				break;
			}

			if ( group->codePointMax() < codePoint )
			{
				// Character group does not encompass this code point.
				continue;
			}

			return group->charInfo(codePoint);
		}

		return nullptr;
	}

	FontCharacterInfo* FontCharacterGroupContainer::invalidGlyphInfo()
	{
		return m_InvalidGlyph;
	}

	const FontCharacterInfo* FontCharacterGroupContainer::invalidGlyphInfo() const
	{
		return m_InvalidGlyph;
	}

	void FontCharacterGroupContainer::addGroup(FontCharacterGroup* group)
	{
		if ( !group )
		{
			return;
		}

		BGRS_ASSERTD(!group->nextGroup(), "Cannot add font character group that is already in a container!");

		if ( !m_LastGroup )
		{
			// Nothing has been set yet - make sure we're initialised.
			m_FirstGroup = group;
		}
		else
		{
			BGRS_ASSERTD(m_LastGroup->codePointMax() < group->codePointMin(), "Cannot add overlapping or out-of-order font character group!");
			m_LastGroup->setNextGroup(group);
		}

		m_LastGroup = group;

		if ( !m_InvalidGlyph && m_LastGroup->codePointMin() == 0 )
		{
			m_InvalidGlyph = m_LastGroup->charInfo(0);
		}
	}
}
