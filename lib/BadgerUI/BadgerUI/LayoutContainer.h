#pragma once

#include <cstddef>
#include <cstdint>
#include "BaseLayout.h"

namespace BadgerUI
{
	template<size_t COUNT>
	class LayoutContainer
	{
	public:
		static constexpr size_t LAYOUT_COUNT = COUNT;

		inline LayoutContainer()
		{
			memset(m_Layouts, 0, sizeof(m_Layouts));
		}

		// Assumes that all added layouts are persistent for the lifetime
		// of the container.
		inline void mapIndexToLayout(int32_t index, BaseLayout* layout)
		{
			if ( !layout || index < 0 || index >= LAYOUT_COUNT )
			{
				return;
			}

			m_Layouts[index] = layout;
		}

		// Returns -1 if there is no active layout set.
		inline int32_t activeLayoutIndex() const
		{
			return m_ActiveLayoutIndex;
		}

		inline bool activeLayoutIsValid() const
		{
			return getLayout(m_ActiveLayoutIndex) != nullptr;
		}

		inline void setActiveLayoutIndex(int32_t index)
		{
			// Ensure "invalid" index is canonically -1.
			if ( index < 0 )
			{
				index = -1;
			}

			if ( index > LAYOUT_COUNT || index == m_ActiveLayoutIndex )
			{
				return;
			}

			switchActiveLayout(index);
		}

		inline DrawableDirtyState updateActiveLayout(const UIUpdateContext& context)
		{
			BaseLayout* const layout = getLayout(m_ActiveLayoutIndex);

			if ( !layout )
			{
				return DrawableDirtyState::NotDirty;
			}

			layout->updateItems(context);
			return layout->dirtyState();
		}

		inline void renderActiveLayout(const UIDrawContext& context)
		{
			BaseLayout* const layout = getLayout(m_ActiveLayoutIndex);

			if ( !layout )
			{
				return;
			}

			// Enforce that we draw everything if we haven't drawn this layout before.
			const DrawableDirtyState dirtyState = m_LayoutRedrawRequired
				? DrawableDirtyState::ContainerDirty
				: layout->dirtyState();

			switch ( dirtyState )
			{
				case DrawableDirtyState::ContainerDirty:
				{
					layout->drawAllItems(context);
					break;
				}

				case DrawableDirtyState::ItemDirty:
				{
					layout->drawDirtyItems(context);
					break;
				}

				default:
				{
					break;
				}
			}

			// What was drawn to the screen is definitely now current.
			m_LayoutRedrawRequired = false;
		}

	private:
		inline BaseLayout* getLayout(int32_t index) const
		{
			return (index >= 0 && index < LAYOUT_COUNT) ? m_Layouts[index] : nullptr;
		}

		inline void switchActiveLayout(int32_t newIndex)
		{
			BaseLayout* layout = getLayout(m_ActiveLayoutIndex);

			if ( layout )
			{
				layout->deactivate();
			}

			// When we change the active layout in any way, flag that this requires a full redraw.
			m_ActiveLayoutIndex = newIndex;
			m_LayoutRedrawRequired = true;

			layout = getLayout(m_ActiveLayoutIndex);

			if ( layout )
			{
				layout->activate();
			}
		}

		BaseLayout* m_Layouts[LAYOUT_COUNT];
		int32_t m_ActiveLayoutIndex = -1;
		bool m_LayoutRedrawRequired = true;
	};
}
