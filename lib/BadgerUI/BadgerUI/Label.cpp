#include <BadgerGL/StringRenderer.h>
#include "Label.h"

namespace BadgerUI
{
	Label::Label() :
		Box()
	{
		// Default to having no outline.
		setDrawStyle(BadgerGL::ShapeDrawStyle::Outline);
		setOutlineWidth(0);
	}

	const char* Label::text() const
	{
		return m_Text;
	}

	void Label::setText(const char* txt)
	{
		if ( txt != m_Text )
		{
			m_RecalculateStringWidth = true;
		}

		setPropertyIfDifferent(m_Text, txt);
	}

	const BadgerGL::BitmapMaskFont* Label::font() const
	{
		return m_Font;
	}

	void Label::setFont(const BadgerGL::BitmapMaskFont* fnt)
	{
		setPropertyIfDifferent(m_Font, fnt);
	}

	const ColourProperty& Label::textColour() const
	{
		return m_TextColour;
	}

	void Label::setTextColour(const ColourProperty& col)
	{
		setPropertyIfDifferent(m_TextColour, col);
	}

	HAlignment Label::horizontalAlignment() const
	{
		return m_HAlignment;
	}

	void Label::setHorizontalAlignment(HAlignment align)
	{
		setPropertyIfDifferent(m_HAlignment, align);
	}

	VAlignment Label::verticalAlignment() const
	{
		return m_VAlignment;
	}

	void Label::setVerticalAlignment(VAlignment align)
	{
		m_VAlignment = align;
	}

	int16_t Label::xShift() const
	{
		return m_XShift;
	}

	void Label::setXShift(int16_t shift)
	{
		setPropertyIfDifferent(m_XShift, shift);
	}

	void Label::delegatedUpdate(const UIUpdateContext& context)
	{
		if ( m_RecalculateStringWidth )
		{
			m_StringWidth = (m_Font && m_Text && *m_Text)
				? BadgerGL::StringRenderer::calculateStringWidth(m_Font, m_Text)
				: 0;

			m_RecalculateStringWidth = false;
		}
	}

	void Label::delegatedDraw(const UIDrawContext& context)
	{
		if ( shouldDrawBox() )
		{
			Box::delegatedDraw(context);
		}

		if ( !m_Font || m_StringWidth < 1 )
		{
			return;
		}

		const UIPoint adjustment(horizontalAlignmentShift() + m_XShift, verticalAlignmentShift());

		context.renderer->setFont(m_Font);
		context.renderer->setPrimaryColour(m_TextColour.schemeColour(*context.colourScheme));
		context.renderer->drawString(m_Text, rect(), adjustment);
	}

	bool Label::shouldDrawBox() const
	{
		return drawStyle() != BadgerGL::ShapeDrawStyle::Outline || outlineWidth() > 0;
	}

	// This is the number of pixels that the left of the string should be away
	// from the left of the target rectangle.
	int16_t Label::horizontalAlignmentShift() const
	{
		switch ( m_HAlignment )
		{
			case HAlignment::Centre:
			{
				return (static_cast<int16_t>(rect().width()) / 2) - (static_cast<int16_t>(m_StringWidth) / 2);
			}

			case HAlignment::Right:
			{
				return static_cast<int16_t>(m_StringWidth) - static_cast<int16_t>(rect().width());
			}

			default:
			{
				return 0;
			}
		}
	}

	// This is the number of pixels that the top of the string should be away
	// from the top of the target rectangle.
	int16_t Label::verticalAlignmentShift() const
	{
		if ( !m_Font )
		{
			return 0;
		}

		switch ( m_VAlignment )
		{
			case VAlignment::Centre:
			{
				return (static_cast<int16_t>(rect().height()) / 2) - (m_Font->lineHeight() / 2);
			}

			case VAlignment::Bottom:
			{
				return static_cast<int16_t>(rect().height()) - m_Font->lineHeight();
			}

			default:
			{
				return 0;
			}
		}
	}
}
