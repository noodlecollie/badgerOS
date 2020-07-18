#pragma once

#include "BaseUIDrawable.h"

namespace BadgerUI
{
	class BaseLayout
	{
	public:
		BaseUIDrawable* itemListHead() const;
		BaseUIDrawable* itemListTail() const;

		DrawableDirtyState dirtyState() const;

		virtual void setup();

		void updateItems(const UIUpdateContext& context);
		void drawDirtyItems(const UIDrawContext& context);
		void drawAllItems(const UIDrawContext& context);

	protected:
		void addItemToHead(BaseUIDrawable* item);
		void addItemToTail(BaseUIDrawable* item);

	private:
		void drawItems(const UIDrawContext& context, bool forceDraw);

		BaseUIDrawable* m_ItemHead = nullptr;
		BaseUIDrawable* m_ItemTail = nullptr;
		DrawableDirtyState m_DirtyState = ItemDirty;
	};
}
