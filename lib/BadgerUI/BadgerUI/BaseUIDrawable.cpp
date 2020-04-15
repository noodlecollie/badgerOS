#include "BaseUIDrawable.h"

namespace BadgerUI
{
	BaseUIDrawable::BaseUIDrawable()
	{
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
		return m_DirtyState;
	}

	void BaseUIDrawable::draw(const UIDrawContext& context)
	{
		if ( m_Callbacks.draw )
		{
			m_Callbacks.draw(context);
		}

		setDirtyState(DrawableDirtyState::NotDirty);
	}

	void BaseUIDrawable::setDirtyState(DrawableDirtyState state)
	{
		m_DirtyState = state;
	}
}
