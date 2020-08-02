#pragma once

#include <cstdint>

namespace BadgerUI
{
	class ButtonInputRecorder
	{
	public:
		inline bool IsPressed(uint32_t button) const
		{
			return IsPressed(button, m_CurrentButtons);
		}

		inline bool IsReleased(uint32_t button) const
		{
			return !IsPressed(button);
		}

		inline bool WasPressedThisFrame(uint32_t button) const
		{
			return IsPressed(button) && !IsPressed(button, m_LastButtons);
		}

		inline bool WasReleasedThisFrame(uint32_t button) const
		{
			return !IsPressed(button) && IsPressed(button, m_LastButtons);
		}

		inline void Clear()
		{
			m_LastButtons = 0;
			m_CurrentButtons = 0;
		}

		inline void AdvanceFrame()
		{
			m_LastButtons = m_CurrentButtons;
			m_CurrentButtons = 0;
		}

		inline void SetPressed(uint32_t button)
		{
			m_CurrentButtons |= button;
		}

		inline void SetReleased(uint32_t button)
		{
			m_CurrentButtons &= ~button;
		}

	private:
		inline bool IsPressed(uint32_t button, uint32_t data) const
		{
			return (data & button) != 0;
		}

		uint32_t m_CurrentButtons = 0;
		uint32_t m_LastButtons = 0;
	};
}
