#pragma once

#include <cstddef>
#include <cstdint>
#include <CoreUtil/BgrsAssert.h>

namespace CoreUtil
{
	class ConstBlob
	{
	public:
		inline ConstBlob() :
			m_Data(nullptr),
			m_Length(0)
		{
		}

		inline ConstBlob(const void* data, size_t length) :
			m_Data(data),
			m_Length(length)
		{
		}

		inline const void* constData() const
		{
			return m_Data;
		}

		inline const uint8_t* constBytes(uint32_t index = 0) const
		{
			if ( index >= m_Length )
			{
				BGRS_ASSERTD(false, "Index was out of range.");
				return nullptr;
			}

			return static_cast<const uint8_t*>(m_Data);
		}

		inline size_t length() const
		{
			return m_Length;
		}

		inline bool isValid() const
		{
			return m_Data != nullptr && m_Length > 0;
		}

	private:
		const void* m_Data = nullptr;
		size_t m_Length = 0;
	};

	class Blob : public ConstBlob
	{
	public:
		inline Blob() :
			ConstBlob()
		{
		}

		inline Blob(void* data, size_t length) :
			ConstBlob(data, length)
		{
		}

		// The following const_casts are OK, since we know that the data passed in originally was non-const.

		inline void* data()
		{
			return const_cast<void*>(constData());
		}

		inline uint8_t* bytes(uint32_t index = 0)
		{
			return const_cast<uint8_t*>(constBytes(index));
		}
	};
}
