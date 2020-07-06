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

	protected:
		virtual void delegatedDraw(const UIDrawContext& context) override;
		virtual DrawableDirtyState delegatedDirtyState() const override;

	private:
		BaseUIDrawable* m_Target = nullptr;
	};
}
