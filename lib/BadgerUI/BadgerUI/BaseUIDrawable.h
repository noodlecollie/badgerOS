#pragma once

#include <functional>
#include <CoreUtil/TimeHelpers.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include <BadgerGL/BitmapMaskBlitter.h>
#include "ColourScheme.h"
#include "Types.h"
#include "FontDirectory.h"

namespace BadgerUI
{
	enum DrawableDirtyState
	{
		NotDirty,
		ItemDirty,
		ContainerDirty	// If the item requires its container to be redrawn
	};

	struct UIUpdateContext
	{
		// Number of miliseconds since the badge was turned on.
		// Note that according to documentation, this overflows roughly every 50 days.
		// Don't do any long-term timestamp recording with this.
		CoreUtil::TimevalMs currentTimeMs = 0;
	};

	struct UIDrawContext
	{
		// These items are guaranteed to be valid when a draw call is made.
		const BadgerGL::BitmapSurface* screenBuffer = nullptr;
		BadgerGL::BitmapRenderer* renderer = nullptr;
		const ColourScheme* colourScheme = nullptr;
		const FontDirectory* fontDirectory = nullptr;
	};

	class BaseUIDrawable
	{
	public:
		// Returns the dirty state. The default implementation just returns
		// the dirty state variable's value, but overrides can be used to modify
		// this behaviour - see delegatedDirtyState().
		DrawableDirtyState dirtyState() const;

		// Update the internal state of the item for this frame.
		void update(const UIUpdateContext& context);

		// Redraws the item, regardless of its dirty state.
		void draw(const UIDrawContext& context);

		BaseUIDrawable* prev() const;
		void setPrev(BaseUIDrawable* item);

		BaseUIDrawable* next() const;
		void setNext(BaseUIDrawable* item);

		const UIRect& rect() const;

	protected:
		BaseUIDrawable();

		// Override these functions in subclases to implement custom behaviour.
		virtual DrawableDirtyState delegatedDirtyState() const;
		virtual void delegatedUpdate(const UIUpdateContext& context);
		virtual void delegatedDraw(const UIDrawContext& context);

		void setDirtyStateInternal(DrawableDirtyState state);
		void setRectInternal(const UIRect& r);

		// If the incoming value is different to the existing property,
		// updates the existing property and also sets the dirty state.
		// operator ==() is used to test equality.
		template<typename T>
		inline void setPropertyIfDifferent(T& property, const T& newValue, DrawableDirtyState newDirtyState = ItemDirty)
		{
			if ( property != newValue )
			{
				property = newValue;
				setDirtyStateInternal(newDirtyState);
			}
		}

	private:
		UIRect m_Rect;
		DrawableDirtyState m_DirtyState = ItemDirty;
		BaseUIDrawable* m_Prev = nullptr;
		BaseUIDrawable* m_Next = nullptr;
	};
}
