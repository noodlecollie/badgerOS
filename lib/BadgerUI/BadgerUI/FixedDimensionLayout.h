#pragma once

#include <cstdint>
#include "BaseLayout.h"

namespace BadgerUI
{
	class FixedDimensionLayout : public BaseLayout
	{
	public:
		FixedDimensionLayout(uint16_t width, uint16_t height);

		inline uint16_t layoutWidth() const
		{
			return m_Width;
		}

		inline uint16_t layoutHeight() const
		{
			return m_Height;
		}

	private:
		uint16_t m_Width = 0;
		uint16_t m_Height = 0;
	};
}
