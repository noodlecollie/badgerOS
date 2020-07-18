#pragma once

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
		void setText(const char* txt);

		const BadgerGL::BitmapMaskFont* font() const;
		void setFont(const BadgerGL::BitmapMaskFont* fnt);

		const ColourProperty& textColour() const;
		void setTextColour(const ColourProperty& col);

		HAlignment horizontalAlignment() const;
		void setAlignment(HAlignment align);

		int16_t xShift() const;
		void setXShift(int16_t shift);

	protected:
		virtual void delegatedUpdate(const UIUpdateContext& context) override;
		virtual void delegatedDraw(const UIDrawContext& context) override;

	private:
		bool shouldDrawBox() const;

		const char* m_Text = nullptr;
		bool m_RecalculateStringWidth = false;
		ColourProperty m_TextColour;
		HAlignment m_HAlignment = HAlignment::Left;
		const BadgerGL::BitmapMaskFont* m_Font = nullptr;
		int16_t m_XShift = 0;

		size_t m_StringWidth = 0;
	};
}
