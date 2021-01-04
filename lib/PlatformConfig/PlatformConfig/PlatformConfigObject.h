#pragma once

#include <CoreUtil/BgrsAssert.h>
#include <PlatformConfig/ConfigArgs.h>
#include <PlatformConfig/Serial.h>
#include <PlatformConfig/SPI.h>
#include <PlatformConfig/ChipSelect.h>
#include <PlatformConfig/I2C.h>
#include <SSD1351/OLEDDriver.h>
#include <InkyImpression/InkyDriver.h>

namespace PlatformConfig
{
	class PlatformConfigObject
	{
	public:
		using SerialConfig = PlatformConfig::SerialConfig;
		using SPIConfig = PlatformConfig::SPIConfig;
		using SPIPinConfig = PlatformConfig::SPIPinConfig;
		using ChipSelectConfig = PlatformConfig::ChipSelectConfig;
		using I2CConfig = PlatformConfig::I2CConfig;
		using SSD1351Config = SSD1351::OLEDDriver::Config;
		using InkyImpressionConfig = InkyImpression::InkyDriver::Config;

		void initialise(const ConfigArgs& args);
		const ConfigArgs& args() const;

		template<typename T>
		inline const T* getElement(bool optional = false) const
		{
			const T* out = nullptr;
			getElementDelegated(out);

			BGRS_ASSERT(optional || out, "Required config element was not provided!");

			return out;
		}

		template<typename T, typename FUNC>
		inline void initialiseSubsystem(const FUNC& initFunc) const
		{
			BGRS_ASSERT(initFunc, "No initialisation function was provided.");

			initFunc(*getElement<T>(false));
		}

	protected:
		virtual void initialiseDelegated(const ConfigArgs& args) = 0;

		// Override these to provide different config variants:

		virtual void getElementDelegated(const SerialConfig*&) const
		{
		}

		virtual void getElementDelegated(const SPIConfig*&) const
		{
		}

		virtual void getElementDelegated(const SPIPinConfig*&) const
		{
		}

		virtual void getElementDelegated(const ChipSelectConfig*&) const
		{
		}

		virtual void getElementDelegated(const I2CConfig*&) const
		{
		}

		virtual void getElementDelegated(const SSD1351Config*&) const
		{
		}

		virtual void getElementDelegated(const InkyImpressionConfig*&) const
		{
		}

	private:
		ConfigArgs m_ConfigArgs;
	};
}
