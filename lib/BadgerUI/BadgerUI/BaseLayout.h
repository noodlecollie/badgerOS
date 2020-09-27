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

		void setup();
		void activate();
		void deactivate();

		bool isActive() const;

		void updateItems(const UIUpdateContext& context);
		void drawDirtyItems(const UIDrawContext& context);
		void drawAllItems(const UIDrawContext& context);

	protected:
		void addItemToHead(BaseUIDrawable* item);
		void addItemToTail(BaseUIDrawable* item);

		virtual void onSetup();
		virtual void onPreUpdate(const UIUpdateContext& context);
		virtual void onPostUpdate(const UIUpdateContext& context);
		virtual void onActivate();
		virtual void onDeactivate();

	private:
		void drawItems(const UIDrawContext& context, bool forceDraw);

		BaseUIDrawable* m_ItemHead = nullptr;
		BaseUIDrawable* m_ItemTail = nullptr;
		DrawableDirtyState m_DirtyState = ItemDirty;
		bool m_Active = false;
	};
}
