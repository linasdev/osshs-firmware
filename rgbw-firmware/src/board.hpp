/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_BOARD_HPP
#define PRETTYHOME_BOARD_HPP

#include <modm/platform.hpp>

namespace prettyhome
{
	namespace board
	{
		using namespace modm::literals;

		struct SystemClock
		{
			static constexpr uint32_t Frequency = 72_MHz;
			static constexpr uint32_t Ahb = Frequency;
			static constexpr uint32_t Apb1 = Frequency / 2;
			static constexpr uint32_t Apb2 = Frequency;

			static constexpr uint32_t Adc  = Apb2;

			static constexpr uint32_t Spi1 = Apb2;
			static constexpr uint32_t Spi2 = Apb1;
			static constexpr uint32_t Spi3 = Apb1;

			static constexpr uint32_t Usart1 = Apb2;
			static constexpr uint32_t Usart2 = Apb1;
			static constexpr uint32_t Usart3 = Apb1;
			static constexpr uint32_t Uart4  = Apb1;
			static constexpr uint32_t Uart5  = Apb1;

			static constexpr uint32_t Can    = Apb1;

			static constexpr uint32_t I2c1   = Apb1;
			static constexpr uint32_t I2c2   = Apb1;

			static constexpr uint32_t Apb1Timer = Apb1 * 2;
			static constexpr uint32_t Apb2Timer = Apb2 * 1;
			static constexpr uint32_t Timer1  = Apb2Timer;
			static constexpr uint32_t Timer2  = Apb1Timer;
			static constexpr uint32_t Timer3  = Apb1Timer;
			static constexpr uint32_t Timer4  = Apb1Timer;
		};

		inline void
		initialize()
		{
			modm::platform::Rcc::enableExternalCrystal();
			modm::platform::Rcc::enablePll(modm::platform::Rcc::PllSource::ExternalCrystal, 9);
			modm::platform::Rcc::setFlashLatency<SystemClock::Frequency>();
			modm::platform::Rcc::enableSystemClock(modm::platform::Rcc::SystemClockSource::Pll);
			modm::platform::Rcc::setAhbPrescaler(modm::platform::Rcc::AhbPrescaler::Div1);
			modm::platform::Rcc::setApb1Prescaler(modm::platform::Rcc::Apb1Prescaler::Div2);
			modm::platform::Rcc::setApb2Prescaler(modm::platform::Rcc::Apb2Prescaler::Div1);
			modm::platform::Rcc::updateCoreFrequency<SystemClock::Frequency>();

			modm::platform::SysTickTimer::initialize<SystemClock>();
		}
	}
}

#endif	// PRETTYHOME_BOARD_HPP