#include "UIDrawableAlias.h"

namespace BadgerUI
{
	UIDrawableAlias::UIDrawableAlias() :
		BaseUIDrawable()
	{
		setDrawCallback(&UIDrawableAlias::privateDraw);
		setDirtyStateDelegate(&UIDrawableAlias::privateDirtyState);
	}

	BaseUIDrawable* UIDrawableAlias::target() const
	{
		return m_Target;
	}

	void UIDrawableAlias::setTarget(BaseUIDrawable* item)
	{
		setPropertyIfDifferent(m_Target, item);
	}

	UIPoint UIDrawableAlias::position()
	{
		return rect().min();
	}

	void UIDrawableAlias::setPosition(const UIPoint& pos)
	{
		setRectInternal(UIRect(pos, 0, 0));
	}

	void UIDrawableAlias::privateDraw(const UIDrawContext& context)
	{
		if ( !m_Target )
		{
			return;
		}

		const BadgerGL::Point16 oldDrawingOffset = context.renderer->drawingOffset();
		context.renderer->setDrawingOffset(position());

		m_Target->draw(context);

		context.renderer->setDrawingOffset(oldDrawingOffset);
	}

	DrawableDirtyState UIDrawableAlias::privateDirtyState() const
	{
		const DrawableDirtyState localDirtyState = dirtyStateInternal();

		if ( !m_Target )
		{
			return localDirtyState;
		}

		const DrawableDirtyState targetDirtyState = m_Target->dirtyState();
		return targetDirtyState > localDirtyState ? targetDirtyState : localDirtyState;
	}
}
