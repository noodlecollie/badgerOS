#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>

namespace BadgerGL
{
	enum class PatternDirection
	{
		Horizontal = 0,
		Vertical
	};

	// Bit gradient values go from 0 to this number inclusive.
	static constexpr size_t MAX_BIT_GRADIENT = 8;

	// Specified in bits of primary colour per 8 bits.
	// Easy half-byte is designed to be repeated along a row/column.
	static constexpr uint32_t BIT_GRADIENT[MAX_BIT_GRADIENT + 1] =
	{
		// 0/8
		0x00000000UL,

		// 1/8
		static_cast<uint32_t>(
			(0b0010 << 28) |
			(0b0000 << 24) |
			(0b1000 << 20) |
			(0b0000 << 16) |
			(0b0001 << 12) |
			(0b0000 << 8) |
			(0b0100 << 4) |
			(0b0000 << 0)),

		// 2/8
		static_cast<uint32_t>(
			(0b0010 << 28) |
			(0b0100 << 24) |
			(0b0001 << 20) |
			(0b1000 << 16) |
			(0b0010 << 12) |
			(0b0100 << 8) |
			(0b0001 << 4) |
			(0b1000 << 0)),

		// 3/8
		static_cast<uint32_t>(
			(0b0010 << 28) |
			(0b0101 << 24) |
			(0b1000 << 20) |
			(0b0110 << 16) |
			(0b0001 << 12) |
			(0b1010 << 8) |
			(0b0100 << 4) |
			(0b1001 << 0)),

		// 4/8
		static_cast<uint32_t>(
			(0b0101 << 28) |
			(0b1010 << 24) |
			(0b0101 << 20) |
			(0b1010 << 16) |
			(0b0101 << 12) |
			(0b1010 << 8) |
			(0b0101 << 4) |
			(0b1010 << 0)),

		// 5/8
		static_cast<uint32_t>(
			(0b1101 << 28) |
			(0b1010 << 24) |
			(0b0111 << 20) |
			(0b1001 << 16) |
			(0b1110 << 12) |
			(0b0101 << 8) |
			(0b1011 << 4) |
			(0b0110 << 0)),

		// 6/8
		static_cast<uint32_t>(
			(0b1101 << 28) |
			(0b1011 << 24) |
			(0b1110 << 20) |
			(0b0111 << 16) |
			(0b1101 << 12) |
			(0b1011 << 8) |
			(0b1110 << 4) |
			(0b0111 << 0)),

		// 7/8
		static_cast<uint32_t>(
			(0b1101 << 28) |
			(0b1111 << 24) |
			(0b0111 << 20) |
			(0b1111 << 16) |
			(0b1110 << 12) |
			(0b1111 << 8) |
			(0b1011 << 4) |
			(0b1111 << 0)),

		// 8/8
		0xFFFFFFFFUL
	};

	class VerticalPatternBitmapData
	{
	public:
		// One byte per row
		static constexpr size_t NUM_ROWS = 8;
		static constexpr size_t NUM_COLS = 4;
		static constexpr size_t TOTAL_BYTES = NUM_ROWS;

		inline constexpr VerticalPatternBitmapData(uint32_t pattern = 0) :
			m_Data
			{
				static_cast<uint8_t>((pattern >> 28) & 0x0F),
				static_cast<uint8_t>((pattern >> 24) & 0x0F),
				static_cast<uint8_t>((pattern >> 20) & 0x0F),
				static_cast<uint8_t>((pattern >> 16) & 0x0F),
				static_cast<uint8_t>((pattern >> 12) & 0x0F),
				static_cast<uint8_t>((pattern >> 8) & 0x0F),
				static_cast<uint8_t>((pattern >> 4) & 0x0F),
				static_cast<uint8_t>((pattern >> 0) & 0x0F)
			}
		{
		}

		inline constexpr const uint8_t* constData() const
		{
			return m_Data;
		}

	private:
		uint8_t m_Data[TOTAL_BYTES];
	};

	class HorizontalPatternBitmapData
	{
	public:
		// One byte per row
		static constexpr size_t NUM_ROWS = 4;
		static constexpr size_t NUM_COLS = 8;
		static constexpr size_t TOTAL_BYTES = NUM_ROWS;

		inline constexpr HorizontalPatternBitmapData(uint32_t pattern = 0) :
			m_Data
			{
				static_cast<uint8_t>(
					((pattern & 0x80000000) >> 24) |
					((pattern & 0x08000000) >> 21) |
					((pattern & 0x00800000) >> 18) |
					((pattern & 0x00080000) >> 15) |
					((pattern & 0x00008000) >> 12) |
					((pattern & 0x00000800) >> 9) |
					((pattern & 0x00000080) >> 6) |
					((pattern & 0x00000008) >> 3)
				),

				static_cast<uint8_t>(
					((pattern & 0x40000000) >> 23) |
					((pattern & 0x04000000) >> 20) |
					((pattern & 0x00400000) >> 17) |
					((pattern & 0x00040000) >> 14) |
					((pattern & 0x00004000) >> 11) |
					((pattern & 0x00000400) >> 8) |
					((pattern & 0x00000040) >> 5) |
					((pattern & 0x00000004) >> 2)
				),

				static_cast<uint8_t>(
					((pattern & 0x20000000) >> 22) |
					((pattern & 0x02000000) >> 19) |
					((pattern & 0x00200000) >> 16) |
					((pattern & 0x00020000) >> 13) |
					((pattern & 0x00002000) >> 10) |
					((pattern & 0x00000200) >> 7) |
					((pattern & 0x00000020) >> 4) |
					((pattern & 0x00000002) >> 1)
				),

				static_cast<uint8_t>(
					((pattern & 0x10000000) >> 21) |
					((pattern & 0x01000000) >> 18) |
					((pattern & 0x00100000) >> 15) |
					((pattern & 0x00010000) >> 12) |
					((pattern & 0x00001000) >> 9) |
					((pattern & 0x00000100) >> 6) |
					((pattern & 0x00000010) >> 3) |
					((pattern & 0x00000001) >> 0)
				)
			}
		{
		}

		inline constexpr const uint8_t* constData() const
		{
			return m_Data;
		}

	private:
		uint8_t m_Data[TOTAL_BYTES];
	};
}
