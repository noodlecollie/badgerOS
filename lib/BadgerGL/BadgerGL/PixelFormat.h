#pragma once

#include <cstdint>
#include "Defs.h"

namespace BadgerGL
{
	struct PixelFormat
	{
		enum class ChannelLayout
		{
			ARGB,
			RGBA,
			RGB,
			PaletteIndex
		};

		static constexpr uint8_t MAX_CHANNELS = 4;

		constexpr inline size_t totalBitDepth() const
		{
			return channelBitDepth[0] + channelBitDepth[1] + channelBitDepth[2] + channelBitDepth[3];
		}

		constexpr inline size_t totalByteDepth() const
		{
			return bitDepthToByteDepth(totalBitDepth());
		}

		ChannelLayout layout;
		uint8_t numChannels;
		uint8_t channelBitDepth[MAX_CHANNELS];
	};

	static constexpr PixelFormat PIXELFORMAT_0RGB =
	{
		.layout = PixelFormat::ChannelLayout::ARGB,
		.numChannels = 4,
		.channelBitDepth = { 4, 4, 4, 4 }
	};

	static constexpr PixelFormat PIXELFORMAT_RGB0 =
	{
		.layout = PixelFormat::ChannelLayout::RGBA,
		.numChannels = 4,
		.channelBitDepth = { 4, 4, 4, 4 }
	};

	static constexpr PixelFormat PIXELFORMAT_65K =
	{
		.layout = PixelFormat::ChannelLayout::RGB,
		.numChannels = 3,
		.channelBitDepth = { 5, 6, 5 }
	};

	static constexpr PixelFormat PIXELFORMAT_PALETTE256 =
	{
		.layout = PixelFormat::ChannelLayout::PaletteIndex,
		.numChannels = 1,
		.channelBitDepth = { 8 }
	};
};
