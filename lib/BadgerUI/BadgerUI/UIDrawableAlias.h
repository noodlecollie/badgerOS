#pragma once

#include "BaseUIDrawable.h"

namespace BadgerUI
{
	class UIDrawableAlias : public BaseUIDrawable
	{
	public:
		UIDrawableAlias();

		BaseUIDrawable* target() const;
		void setTarget(BaseUIDrawable* item);

		UIPoint position();
		void setPosition(const UIPoint& pos);

	private:
		void privateDraw(const UIDrawContext& context);
		DrawableDirtyState privateDirtyState() const;

		BaseUIDrawable* m_Target = nullptr;
	};
}
