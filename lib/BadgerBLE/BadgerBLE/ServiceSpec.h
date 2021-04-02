#pragma once

#include <cstddef>
#include <BadgerBLE/GATTDefs.h>

namespace BadgerBLE
{
	class ServiceSpec
	{
	public:
		inline constexpr ServiceSpec(const ServiceDef& service, const CharacteristicDef* chDefs, size_t chCount) :
			m_ServiceDef(service),
			m_Characteristics(chDefs),
			m_CharacteristicCount(chCount)
		{
		}

		template<size_t SIZE>
		inline constexpr ServiceSpec(const ServiceDef& service, const CharacteristicDef (&chDefs)[SIZE]) :
			m_ServiceDef(service),
			m_Characteristics(chDefs),
			m_CharacteristicCount(SIZE)
		{
		}

		constexpr const ServiceDef& service() const
		{
			return m_ServiceDef;
		}

		// We have to assume that the index is valid because this is a constexpr function.
		constexpr const CharacteristicDef& characteristic(size_t index) const
		{
			return m_Characteristics[index];
		}

		constexpr size_t characteristicCount() const
		{
			return m_CharacteristicCount;
		}

		constexpr const CharacteristicDef& operator [](size_t index) const
		{
			return characteristic(index);
		}

	private:
		const ServiceDef& m_ServiceDef;
		const CharacteristicDef* m_Characteristics;
		size_t m_CharacteristicCount = 0;
	};
}
