#pragma once

#include <cstdint>
#include <cstddef>

namespace CoreUtil
{
	template<typename T>
	static constexpr inline T rotateBytesDown(T data, uint8_t width = sizeof(T))
	{
		// We want the following to happen, where '*' is data we don't care about:

		// abcd => dabc
		// *abc => *cab
		// **ab => **ba
		// ***a => ***a

		// We need to take the bottom byte and shift this 8 * (width - 1) bits up.
		// We also need to take the other (width - 1) bytes and shift them down 8 bits.

		// The bottom byte is easy: do (data & 0xFF) << (8 * (width - 1))

		// The top bytes are more complicated, because we want to ensure that undefined
		// bits do not interfere with the masking later. This means that they need to be
		// zeroed by bit-shifting up and then down.

		// - If the width is 4, we want to shift up 0 bits and down 8 bits.
		// - If the width is 3, we want to shift up 8 bits and down 16 bits.
		// - If the width is 2, we want to shift up 16 bits and down 24 bits.
		// - If the width is 1 (though this function is pointless in that case), we want
		//   to shift up and down 24 bits.

		// In general, we want to shift up by 8 * (sizeof(T) - width) bits, and then down by
		// (8 * (sizeof(T) - width + 1)) bits.

		// This becomes: (data << (8 * (sizeof(T) - width))) >> (8 * (sizeof(T) - width + 1)).

		return
			(
				// Upper bytes
				data
				<< (8 * (sizeof(T) - width))
				>> (8 * (sizeof(T) - width + 1))
			)
			|
			(	// Lower bytes
				(data & 0xFF) << (8 * (width - 1))
			);
	}

	// Assumes buffers are large enough for the specified number of bits.
	static inline void writeBits(uint8_t* dest, const uint8_t* source, size_t numBits)
	{
		while ( numBits >= 8 )
		{
			*(dest++) = *(source++);
			numBits -= 8;
		}

		if ( numBits > 0 )
		{
			// Shift up and down to ensure that the remaining bits are zeroed.
			*dest = ((*source) << numBits) >> numBits;
		}
	}
}
