#pragma once

#include <cstddef>
#include "Blob.h"

namespace CoreUtil
{
	template<typename T>
	class ConstDataBuffer
	{
	public:
		using DataType = T;

		inline ConstDataBuffer() :
			m_Data(nullptr),
			m_ElementCount(0)
		{
		}

		inline ConstDataBuffer(const DataType* data, size_t elemCount) :
			m_Data(data),
			m_ElementCount(elemCount)
		{
		}

		inline const DataType* constData(size_t elemIndex = 0) const
		{
			return (m_Data && elemIndex < m_ElementCount)
				? &m_Data[elemIndex]
				: nullptr;
		}

		inline const void* constRawData(size_t elemIndex = 0) const
		{
			return static_cast<const void*>(constData(elemIndex));
		}

		inline ConstBlob constBlob() const
		{
			return ConstBlob(constData(), dataSize());
		}

		inline size_t elementCount() const
		{
			return m_ElementCount;
		}

		inline size_t dataSize() const
		{
			return m_ElementCount * sizeof(DataType);
		}

		inline bool isValid() const
		{
			return m_Data != nullptr && m_ElementCount > 0;
		}

	private:
		const DataType* m_Data = nullptr;
		size_t m_ElementCount = 0;
	};

	template<typename T>
	class DataBuffer : public ConstDataBuffer<T>
	{
	public:
		using DataType = T;

		inline DataBuffer() :
			ConstDataBuffer<T>()
		{
		}

		inline DataBuffer(DataType* data, size_t elemCount) :
			ConstDataBuffer<T>(data, elemCount)
		{
		}

		// The following const_casts are OK, since we know that the data passed in originally was non-const.

		inline DataType* data(size_t elemIndex = 0)
		{
			return const_cast<DataType*>(ConstDataBuffer<T>::constData(elemIndex));
		}

		inline void* rawData(size_t elemIndex = 0)
		{
			return const_cast<void*>(ConstDataBuffer<T>::constRawData(elemIndex));
		}

		inline Blob blob()
		{
			return Blob(data(), ConstDataBuffer<T>::dataSize());
		}
	};

	template<typename T, size_t EC>
	class StaticDataBuffer : public DataBuffer<T>
	{
	public:
		using DataType = T;

		static constexpr size_t ELEMENT_SIZE = sizeof(DataType);
		static constexpr size_t ELEMENT_COUNT = EC;
		static constexpr size_t DATA_SIZE = ELEMENT_COUNT * ELEMENT_SIZE;

		StaticDataBuffer() :
			DataBuffer<T>(m_Buffer, ELEMENT_COUNT)
		{
		}

	private:
		DataType m_Buffer[ELEMENT_COUNT];
	};
}
