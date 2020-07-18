#pragma once

#include <cstddef>
#include <cstdint>
#include "BgrsAssert.h"

namespace CoreUtil
{
	template<typename T, typename E, E COUNT>
	class EnumAddressableList
	{
	public:
		using ItemType = T;
		using EnumType = E;

		static constexpr size_t ITEM_COUNT = static_cast<size_t>(COUNT);

		inline T& item(EnumType index)
		{
			BGRS_ASSERTD(static_cast<uint32_t>(index) < ITEM_COUNT, "Enum value was out of range.");
			return m_Items[static_cast<uint32_t>(index)];
		}


		inline const T& item(EnumType index) const
		{
			BGRS_ASSERTD(static_cast<uint32_t>(index) < ITEM_COUNT, "Enum value was out of range.");
			return m_Items[static_cast<uint32_t>(index)];
		}

		inline size_t count() const
		{
			return ITEM_COUNT;
		}

		template<typename FUNC>
		inline void forEach(const FUNC& callback)
		{
			for ( uint32_t index = 0; index < ITEM_COUNT; ++index )
			{
				callback(index, m_Items[index]);
			}
		}

		template<typename FUNC>
		inline void forEach(const FUNC& callback) const
		{
			for ( uint32_t index = 0; index < ITEM_COUNT; ++index )
			{
				callback(index, m_Items[index]);
			}
		}

		inline T& operator [](EnumType index)
		{
			return item(index);
		}

		inline const T& operator [](EnumType index) const
		{
			return item(index);
		}

	protected:
		inline EnumAddressableList(bool zeroAllItems = false)
		{
			if ( zeroAllItems )
			{
				memset(m_Items, 0, sizeof(m_Items));
			}
		}

	private:
		static ItemType m_Items[ITEM_COUNT];
	};

	template<typename T, typename E, E COUNT>
	typename EnumAddressableList<T, E, COUNT>::ItemType EnumAddressableList<T, E, COUNT>::m_Items[EnumAddressableList<T, E, COUNT>::ITEM_COUNT];
}
