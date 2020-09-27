#include "BaseLayout.h"

namespace BadgerUI
{
	BaseUIDrawable* BaseLayout::itemListHead() const
	{
		return m_ItemHead;
	}

	BaseUIDrawable* BaseLayout::itemListTail() const
	{
		return m_ItemTail;
	}

	DrawableDirtyState BaseLayout::dirtyState() const
	{
		return m_DirtyState;
	}

	bool BaseLayout::isActive() const
	{
		return m_Active;
	}

	void BaseLayout::setup()
	{
		onSetup();
	}

	void BaseLayout::addItemToHead(BaseUIDrawable* item)
	{
		if ( !item )
		{
			return;
		}

		if ( m_ItemHead )
		{
			m_ItemHead->setPrev(item);
		}

		item->setNext(m_ItemHead);
		item->setPrev(nullptr);

		m_ItemHead = item;

		if ( !m_ItemTail )
		{
			m_ItemTail = item;
		}
	}

	void BaseLayout::addItemToTail(BaseUIDrawable* item)
	{
		if ( !item )
		{
			return;
		}

		if ( m_ItemTail )
		{
			m_ItemTail->setNext(item);
		}

		item->setPrev(m_ItemTail);
		item->setNext(nullptr);

		m_ItemTail = item;

		if ( !m_ItemHead )
		{
			m_ItemHead = item;
		}
	}

	void BaseLayout::activate()
	{
		if ( m_Active )
		{
			return;
		}

		m_Active = true;
		onActivate();
	}

	void BaseLayout::deactivate()
	{
		if ( !m_Active )
		{
			return;
		}

		onDeactivate();
		m_Active = false;
	}

	void BaseLayout::updateItems(const UIUpdateContext& context)
	{
		onPreUpdate();

		for ( BaseUIDrawable* item = m_ItemHead; item; item = item->next() )
		{
			item->update(context);
			const DrawableDirtyState dirty = item->dirtyState();

			if ( dirty > m_DirtyState )
			{
				m_DirtyState = dirty;
			}
		}

		onPostUpdate();
	}

	void BaseLayout::drawDirtyItems(const UIDrawContext& context)
	{
		drawItems(context, false);
	}

	void BaseLayout::drawAllItems(const UIDrawContext& context)
	{
		drawItems(context, true);
	}

	void BaseLayout::drawItems(const UIDrawContext& context, bool forceDraw)
	{
		for ( BaseUIDrawable* item = m_ItemHead; item; item = item->next() )
		{
			if ( forceDraw || item->dirtyState() > NotDirty )
			{
				item->draw(context);
			}
		}

		m_DirtyState = NotDirty;
	}

	void BaseLayout::onSetup()
	{
		// Implemented in subclasses.
	}

	void BaseLayout::onActivate()
	{
		// Implemented in subclasses.
	}

	void BaseLayout::onDeactivate()
	{
		// Implemented in subclasses.
	}

	void BaseLayout::onPreUpdate()
	{
		// Implemented in subclasses.
	}

	void BaseLayout::onPostUpdate()
	{
		// Implemented in subclasses.
	}
}
