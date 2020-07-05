#pragma once

#include <functional>
#include <CoreUtil/TimeHelpers.h>
#include <BadgerGL/BitmapSurface.h>
#include <BadgerGL/BitmapRenderer.h>
#include "ColourScheme.h"
#include "Types.h"

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
	};

	// Used to avoid the extra CPU/memory overhead of vtables.
	// TODO: std::function requires a virtual function call anyway,
	// apparently, so it'd be better just to make these virtual
	// functions on the object.
	struct UIDrawableCallbacks
	{
		// Update the internal state of the item for this frame.
		std::function<void(const UIUpdateContext&)> update;

		// Redraws the item, regardless of its dirty state.
		std::function<void(const UIDrawContext&)> draw;

		// If specified, this function will be called to retrieve the dirty state
		// when dirtyState() is called on the drawable.
		std::function<DrawableDirtyState(void)> dirtyStateDelegate;
	};

	class BaseUIDrawable
	{
	public:
		DrawableDirtyState dirtyState() const;

		void update(const UIUpdateContext& context);
		void draw(const UIDrawContext& context);

		BaseUIDrawable* prev() const;
		void setPrev(BaseUIDrawable* item);

		BaseUIDrawable* next() const;
		void setNext(BaseUIDrawable* item);

		const UIRect& rect() const;

	protected:
		BaseUIDrawable();

		inline DrawableDirtyState dirtyStateInternal() const
		{
			return m_DirtyState;
		}

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

		// Void return type, non-const member function.
		template<typename DERIVED, typename... ARGS>
		inline void setCallback(std::function<void(ARGS...)> UIDrawableCallbacks::* callbackPtr,
								void (DERIVED::*memberFunction)(ARGS...))
		{
			DERIVED* derivedInstance = static_cast<DERIVED*>(this);

			m_Callbacks.*callbackPtr = [derivedInstance, memberFunction](ARGS... args) -> void
			{
				(derivedInstance->*memberFunction)(args...);
			};
		}

		// Void return type, const member function.
		template<typename DERIVED, typename... ARGS>
		inline void setCallback(std::function<void(ARGS...)> UIDrawableCallbacks::* callbackPtr,
								void (DERIVED::*memberFunction)(ARGS...) const)
		{
			const DERIVED* derivedInstance = static_cast<const DERIVED*>(this);

			m_Callbacks.*callbackPtr = [derivedInstance, memberFunction](ARGS... args) -> void
			{
				(derivedInstance->*memberFunction)(args...);
			};
		}

		// Non-void return type, non-const member function.
		template<typename DERIVED, typename RET, typename... ARGS>
		inline void setCallback(std::function<RET(ARGS...)> UIDrawableCallbacks::* callbackPtr,
								RET (DERIVED::*memberFunction)(ARGS...))
		{
			DERIVED* derivedInstance = static_cast<DERIVED*>(this);

			m_Callbacks.*callbackPtr = [derivedInstance, memberFunction](ARGS... args) -> RET
			{
				return (derivedInstance->*memberFunction)(args...);
			};
		}

		// Non-void return type, const member function.
		template<typename DERIVED, typename RET, typename... ARGS>
		inline void setCallback(std::function<RET(ARGS...)> UIDrawableCallbacks::* callbackPtr,
								RET (DERIVED::*memberFunction)(ARGS...) const)
		{
			const DERIVED* derivedInstance = static_cast<const DERIVED*>(this);

			m_Callbacks.*callbackPtr = [derivedInstance, memberFunction](ARGS... args) -> RET
			{
				return (derivedInstance->*memberFunction)(args...);
			};
		}

		// For convenience:

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

		template<typename DERIVED>
		inline void setDirtyStateDelegate(DrawableDirtyState (DERIVED::*memberFunction)(void) const)
		{
			setCallback(&UIDrawableCallbacks::dirtyStateDelegate, memberFunction);
		}

		UIDrawableCallbacks m_Callbacks;

	private:
		UIRect m_Rect;
		DrawableDirtyState m_DirtyState = ItemDirty;
		BaseUIDrawable* m_Prev = nullptr;
		BaseUIDrawable* m_Next = nullptr;
	};
}
