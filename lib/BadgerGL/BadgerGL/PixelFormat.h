#pragma once

#include <cstdint>
#include "Defs.h"

namespace BadgerGL
{
	enum PixelFormatId
	{
		PixelFormat_0RGB,
		PixelFormat_RGB0,
		PixelFormat_65K,
		PixelFormat_Mono256,	// For palettes

		PixelFormat__Count
	};

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

		constexpr inline bool operator ==(const PixelFormat& other) const
		{
			return id == other.id;
		}

		constexpr inline bool operator !=(const PixelFormat& other) const
		{
			return !(*this == other);
		}

		PixelFormatId id;
		ChannelLayout layout;
		uint8_t numChannels;
		uint8_t channelBitDepth[MAX_CHANNELS];
	};

	static constexpr PixelFormat PIXELFORMAT_65K =
	{
		.id = PixelFormat_65K,
		.layout = PixelFormat::ChannelLayout::RGB,
		.numChannels = 3,
		.channelBitDepth = { 5, 6, 5 }
	};

	static constexpr PixelFormat PIXELFORMAT_MONO256 =
	{
		.id = PixelFormat_Mono256,
		.layout = PixelFormat::ChannelLayout::PaletteIndex,
		.numChannels = 1,
		.channelBitDepth = { 8 }
	};

	const PixelFormat* getPixelFormat(PixelFormatId id);
};
