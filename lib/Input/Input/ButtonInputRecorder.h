#pragma once

#include <cstdint>

namespace Input
{
	class ButtonInputRecorder
	{
	public:
		inline bool isPressed(uint32_t button) const
		{
			return isPressed(button, m_CurrentButtons);
		}

		inline bool isReleased(uint32_t button) const
		{
			return !isPressed(button);
		}

		inline bool wasPressedThisFrame(uint32_t button) const
		{
			return isPressed(button) && !isPressed(button, m_LastButtons);
		}

		inline bool wasReleasedThisFrame(uint32_t button) const
		{
			return !isPressed(button) && isPressed(button, m_LastButtons);
		}

		inline void clear()
		{
			m_LastButtons = 0;
			m_CurrentButtons = 0;
		}

		inline void advanceFrame()
		{
			m_LastButtons = m_CurrentButtons;
			m_CurrentButtons = 0;
		}

		inline void setPressed(uint32_t button)
		{
			m_CurrentButtons |= button;
		}

		inline void setReleased(uint32_t button)
		{
			m_CurrentButtons &= ~button;
		}

	private:
		inline bool isPressed(uint32_t button, uint32_t data) const
		{
			return (data & button) != 0;
		}

		uint32_t m_CurrentButtons = 0;
		uint32_t m_LastButtons = 0;
	};
}
