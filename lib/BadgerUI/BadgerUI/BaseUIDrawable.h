#pragma once

#include <functional>
#include <CoreUtil/TimeHelpers.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include "ColourScheme.h"

namespace BadgerUI
{
	enum class DrawableDirtyState
	{
		NotDirty,
		ItemDirty,
		ScreenDirty	// If the item requires the whole screen to be redrawn.
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
	};

	// Used to avoid the extra CPU/memory overhead of vtables.
	struct UIDrawableCallbacks
	{
		// Update the internal state of the item for this frame.
		std::function<void(const UIUpdateContext&)> update;

		// Redraws the item, regardless of its dirty state.
		std::function<void(const UIDrawContext&)> draw;
	};

	class BaseUIDrawable
	{
	public:
		DrawableDirtyState dirtyState() const;

		void update(const UIUpdateContext& context);
		void draw(const UIDrawContext& context);

	protected:
		BaseUIDrawable();

		void setDirtyState(DrawableDirtyState state);

		// If the incoming value is different to the existing property,
		// updates the existing property and also sets the dirty state.
		// operator ==() is used to test equality.
		template<typename T>
		inline void setPropertyIfDifferent(T& property, const T& newValue, DrawableDirtyState newDirtyState = DrawableDirtyState::ItemDirty)
		{
			if ( property != newValue )
			{
				property = newValue;
				setDirtyState(newDirtyState);
			}
		}

		template<typename DERIVED, typename CTX>
		inline void setCallback(std::function<void(const CTX&)> UIDrawableCallbacks::* callbackPtr,
								void (DERIVED::*memberFunction)(const CTX&))
		{
			DERIVED* derivedInstance = static_cast<DERIVED*>(this);

			m_Callbacks.*callbackPtr = [derivedInstance, memberFunction](const CTX& context)
			{
				(derivedInstance->*memberFunction)(context);
			};
		}

		template<typename DERIVED>
		inline void setUpdateCallback(void (DERIVED::*memberFunction)(const UIUpdateContext&))
		{
			setCallback(&UIDrawableCallbacks::update, memberFunction);
		}

		template<typename DERIVED>
		inline void setDrawCallback(void (DERIVED::*memberFunction)(const UIDrawContext&))
		{
			setCallback(&UIDrawableCallbacks::draw, memberFunction);
		}

		UIDrawableCallbacks m_Callbacks;

	private:
		DrawableDirtyState m_DirtyState = DrawableDirtyState::ItemDirty;
	};
}
