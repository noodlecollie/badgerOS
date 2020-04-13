#pragma once

#include <CoreUtil/BgrsAssert.h>
#include "PixelFormat.h"

namespace BadgerGL
{
	class ConstBitmapBuffer
	{
	public:
		inline ConstBitmapBuffer()
		{
		}

		inline ConstBitmapBuffer(const void* data, size_t lengthInBytes, const PixelFormat* pixelFormat) :
			m_Data(data),
			m_LengthInBytes(lengthInBytes),
			m_PixelFormat(pixelFormat)
		{
		}

		inline bool isValid() const
		{
			return m_Data && m_LengthInBytes > 0 && m_PixelFormat;
		}

		inline const void* constRawData(uint32_t index = 0) const
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Buffer was not valid.");
				return nullptr;
			}

			return static_cast<const void*>(static_cast<const uint8_t*>(m_Data) + (index * m_PixelFormat->totalByteDepth()));
		}

		template<typename T>
		inline const T* constData(uint32_t index = 0) const
		{
			if ( !isValid() )
			{
				BGRS_ASSERTD(false, "Buffer was not valid.");
				return nullptr;
			}

			if ( sizeof(T) != m_PixelFormat->totalByteDepth() )
			{
				BGRS_ASSERTD(false, "Size of pixel type did not match pixel depth.");
				return nullptr;
			}

			return static_cast<const T*>(m_Data) + index;
		}

		inline size_t lengthInBytes() const
		{
			return m_LengthInBytes;
		}

		inline size_t lengthInPixels() const
		{
			return isValid() ? m_LengthInBytes / m_PixelFormat->totalByteDepth() : 0;
		}

		const PixelFormat* pixelFormat() const
		{
			return m_PixelFormat;
		}

	private:
		const void* m_Data = nullptr;
		size_t m_LengthInBytes = 0;
		const PixelFormat* m_PixelFormat = nullptr;
	};

	class BitmapBuffer : public ConstBitmapBuffer
	{
	public:
		inline BitmapBuffer()
		{
		}

		inline BitmapBuffer(void* data, size_t lengthInBytes, const PixelFormat* pixelFormat) :
			ConstBitmapBuffer(data, lengthInBytes, pixelFormat)
		{
		}

		inline void* rawData(uint32_t index = 0) const
		{
			return const_cast<void*>(constRawData(index));
		}

		template<typename T>
		inline T* data(uint32_t index = 0) const
		{
			return const_cast<T*>(constData<T>(index));
		}
	};
}
