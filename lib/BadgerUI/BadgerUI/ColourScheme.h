#pragma once

#include <cstdint>
#include <cstring>

namespace BadgerUI
{
	class ColourScheme
	{
	public:
		enum ColourId
		{
			Colour_Primary = 0,
			Colour_Secondary,

			Colour_Background,
			Colour_BackgroundAlt,

			Colour__Count,
			Colour_Custom = -1
		};

		inline ColourScheme()
		{
			memset(m_Colours, 0, sizeof(m_Colours));
		}

		inline uint32_t colour(ColourId id) const
		{
			return (id >= 0 && id < Colour__Count) ? m_Colours[id] : 0;
		}

		inline void setColour(ColourId id, uint32_t value)
		{
			if ( id >= 0 && id < Colour__Count )
			{
				m_Colours[id] = value;
			}
		}

	private:
		uint32_t m_Colours[Colour__Count];
	};

	class ColourProperty
	{
	public:
		inline ColourProperty()
		{
		}

		inline ColourProperty(ColourScheme::ColourId inId, uint32_t inCustom = 0) :
			m_Id(inId),
			m_CustomColour(inCustom)
		{
		}

		inline ColourScheme::ColourId id() const
		{
			return m_Id;
		}

		inline void setId(ColourScheme::ColourId inId)
		{
			m_Id = inId;
		}

		inline uint32_t customColour() const
		{
			return m_CustomColour;
		}

		inline void setCustomColour(uint32_t custom)
		{
			m_Id = ColourScheme::Colour_Custom;
			m_CustomColour = custom;
		}

		inline uint32_t schemeColour(const ColourScheme& scheme)
		{
			return m_Id != ColourScheme::Colour_Custom
				? scheme.colour(m_Id)
				: m_CustomColour;
		}

		inline bool operator ==(const ColourProperty& other) const
		{
			// If this is a custom colour, the value must match too.
			return m_Id == other.m_Id && (m_Id != ColourScheme::Colour_Custom || m_CustomColour == other.m_CustomColour);
		}

		inline bool operator !=(const ColourProperty& other) const
		{
			return !(*this == other);
		}

	private:
		ColourScheme::ColourId m_Id = ColourScheme::Colour_Primary;
		uint32_t m_CustomColour = 0;
	};
};
