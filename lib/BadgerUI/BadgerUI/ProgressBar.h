#pragma once

#include <cstdint>
#include "BaseUIDrawable.h"
#include "Box.h"

namespace BadgerUI
{
	class ProgressBar : public BaseUIDrawable
	{
	public:
		void setRect(const UIRect& inRect);

		uint8_t outlineWidth() const;
		void setOutlineWidth(uint8_t width);

		const ColourProperty& outlineColour() const;
		void setOutlineColour(const ColourProperty& col);

		const ColourProperty& backgroundColour() const;
		void setBackgroundColour(const ColourProperty& col);

		const ColourProperty& foregroundColour() const;
		void setForegroundColour(const ColourProperty& col);

		// Range: [0.0f 1.0f]
		float filledFraction() const;
		void setFilledFraction(float frac);

	protected:
		virtual void delegatedUpdate(const UIUpdateContext& context) override;
		virtual void delegatedDraw(const UIDrawContext& context) override;

	private:
		void updateBoxRects();
		float interiorWidth() const;

		Box m_Foreground;
		Box m_Background;
		float m_FilledFraction = 0.0f;
		size_t m_FilledWidth = 0;
	};
}
