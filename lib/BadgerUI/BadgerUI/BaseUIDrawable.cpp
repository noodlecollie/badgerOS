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
		if ( m_Callbacks.update )
		{
			m_Callbacks.update(context);
		}
	}

	DrawableDirtyState BaseUIDrawable::dirtyState() const
	{
		return m_Callbacks.dirtyStateDelegate ? m_Callbacks.dirtyStateDelegate() : dirtyStateInternal();
	}

	void BaseUIDrawable::draw(const UIDrawContext& context)
	{
		if ( m_Callbacks.draw )
		{
			m_Callbacks.draw(context);
		}

		setDirtyStateInternal(NotDirty);
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
