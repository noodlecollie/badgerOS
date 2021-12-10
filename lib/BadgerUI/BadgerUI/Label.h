#pragma once

#include <CoreUtil/TimeHelpers.h>
#include <BadgerGL/BitmapMaskFont.h>
#include "Types.h"
#include "Box.h"

namespace BadgerUI
{
	// The label does not own its text, it just keeps a shallow pointer to it.
	// The text is expected to live at least as long as the label.
	class Label : public Box
	{
	public:
		Label();

		const char* text() const;
		void setText(const char* txt, bool strCompare = false);

		const BadgerGL::BitmapMaskFont* font() const;
		void setFont(const BadgerGL::BitmapMaskFont* fnt);

		const ColourProperty& textColour() const;
		void setTextColour(const ColourProperty& col);

		HAlignment horizontalAlignment() const;
		void setHorizontalAlignment(HAlignment align);

		VAlignment verticalAlignment() const;
		void setVerticalAlignment(VAlignment align);

		UIPoint positionAdjustment() const;
		void setPositionAdjustment(const UIPoint& adjust);

		float scrollRate() const;
		void setScrollRate(float pixPerSec);
		void resetScroll();

	protected:
		virtual void delegatedUpdate(const UIUpdateContext& context) override;
		virtual void delegatedDraw(const UIDrawContext& context) override;

	private:
		bool shouldDrawBox() const;
		int16_t horizontalAlignmentShift() const;
		int16_t verticalAlignmentShift() const;

		void updateXShiftFromScroll();

		const char* m_Text = nullptr;
		bool m_RecalculateStringWidth = false;
		ColourProperty m_TextColour;
		HAlignment m_HAlignment = HAlignment::Left;
		VAlignment m_VAlignment = VAlignment::Top;
		const BadgerGL::BitmapMaskFont* m_Font = nullptr;
		UIPoint m_PositionAdjust;
		float m_ScrollRatePPS = 0.0f;

		CoreUtil::TimevalMs m_LastUpdate = 0;
		size_t m_StringWidth = 0;
		float m_XShiftFromScroll = 0;
	};
}
