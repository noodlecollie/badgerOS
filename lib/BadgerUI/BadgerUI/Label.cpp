#include <cmath>
#include <Arduino.h>
#include <BadgerGL/StringRenderer.h>
#include "Label.h"

namespace
{
	inline float offsetMod(float x, float y)
	{
		if ( x >= 0 )
		{
			return std::fmod(x, y);
		}
		else
		{
			return y - std::fmod(-x, y);
		}
	}
}
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

	UIPoint Label::positionAdjustment() const
	{
		return m_PositionAdjust;
	}

	void Label::setPositionAdjustment(const UIPoint& adjust)
	{
		m_PositionAdjust = adjust;
	}

	float Label::scrollRate() const
	{
		return m_ScrollRatePPS;
	}

	void Label::setScrollRate(float pixPerSec)
	{
		m_ScrollRatePPS = pixPerSec;
	}

	void Label::resetScroll()
	{
		m_XShiftFromScroll = 0.0f;
	}

	void Label::delegatedUpdate(const UIUpdateContext&)
	{
		if ( m_LastUpdate == 0 )
		{
			m_LastUpdate = millis();
		}

		if ( m_RecalculateStringWidth )
		{
			m_StringWidth = (m_Font && m_Text && *m_Text)
				? BadgerGL::StringRenderer::calculateStringWidth(m_Font, m_Text)
				: 0;

			m_RecalculateStringWidth = false;
		}

		if ( m_ScrollRatePPS != 0.0f && m_StringWidth > 0 )
		{
			updateXShiftFromScroll();
		}

		m_LastUpdate = millis();
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

		const int16_t hAlignShift = horizontalAlignmentShift();
		const float rectWidth = static_cast<float>(rect().width());
		const float stringWidth = static_cast<float>(m_StringWidth);

		// m_XShiftFromScroll is in the range [0   stringWidth + rectWidth).
		// We want to add it to the existing X offset for horizontal alignment,
		// and then perform a modulo on the offset.
		float xShift = hAlignShift + m_XShiftFromScroll;
		xShift = offsetMod(xShift + stringWidth, rectWidth + stringWidth) - stringWidth;
		xShift += m_PositionAdjust.x();

		const UIPoint adjustment(UIPoint(xShift, verticalAlignmentShift() + m_PositionAdjust.y()));

		context.renderer->setFont(m_Font);
		context.renderer->setPrimaryColour(m_TextColour.schemeColour(*context.colourScheme));
		context.renderer->drawString(m_Text, rect(), adjustment);
	}

	bool Label::shouldDrawBox() const
	{
		return drawStyle() != BadgerGL::ShapeDrawStyle::Outline || outlineWidth() > 0;
	}

	void Label::updateXShiftFromScroll()
	{
		const CoreUtil::TimevalMs elapsedTimeMs = millis() - m_LastUpdate;

		if ( elapsedTimeMs < 1 )
		{
			return;
		}

		const float elapsedTimeSecs = static_cast<float>(elapsedTimeMs) / 1000.0f;
		const float maxDistanceFromZero = static_cast<float>(rect().width() + m_StringWidth);
		const float delta = m_ScrollRatePPS * elapsedTimeSecs;

		float newXShift = m_XShiftFromScroll + delta;
		newXShift = offsetMod(newXShift, maxDistanceFromZero);

		setPropertyIfDifferent(m_XShiftFromScroll, newXShift);
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
				return static_cast<int16_t>(rect().width()) - static_cast<int16_t>(m_StringWidth);
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
