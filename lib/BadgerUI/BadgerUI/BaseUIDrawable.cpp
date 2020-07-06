#include "BaseUIDrawable.h"

namespace BadgerUI
{
	BaseUIDrawable::BaseUIDrawable()
	{
	}

	BaseUIDrawable* BaseUIDrawable::prev() const
	{
		return m_Prev;
	}

	void BaseUIDrawable::setPrev(BaseUIDrawable* item)
	{
		m_Prev = item;
	}

	BaseUIDrawable* BaseUIDrawable::next() const
	{
		return m_Next;
	}

	void BaseUIDrawable::setNext(BaseUIDrawable* item)
	{
		m_Next = item;
	}

	const UIRect& BaseUIDrawable::rect() const
	{
		return m_Rect;
	}

	void BaseUIDrawable::update(const UIUpdateContext& context)
	{
		delegatedUpdate(context);
	}

	DrawableDirtyState BaseUIDrawable::dirtyState() const
	{
		return delegatedDirtyState();
	}

	void BaseUIDrawable::draw(const UIDrawContext& context)
	{
		delegatedDraw(context);
		setDirtyStateInternal(NotDirty);
	}

	DrawableDirtyState BaseUIDrawable::delegatedDirtyState() const
	{
		return m_DirtyState;
	}

	void BaseUIDrawable::delegatedUpdate(const UIUpdateContext& context)
	{
		// Nothing
	}

	void BaseUIDrawable::delegatedDraw(const UIDrawContext& context)
	{
		// Nothing
	}

	void BaseUIDrawable::setDirtyStateInternal(DrawableDirtyState state)
	{
		m_DirtyState = state;
	}

	void BaseUIDrawable::setRectInternal(const UIRect& r)
	{
		setPropertyIfDifferent(m_Rect, r);
	}
}
