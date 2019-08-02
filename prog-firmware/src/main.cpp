/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/log/logger.hpp>

#include <prettyhome/system.hpp>
#include <prettyhome/interfaces/uart_interface.hpp>
#include <prettyhome/interfaces/can_interface.hpp>
#include <prettyhome/modules/eeprom_module.hpp>
#include <prettyhome/modules/pwm_module.hpp>

#include "./board.hpp"

using namespace modm::literals;

#undef	MODM_LOG_LEVEL
#define	MODM_LOG_LEVEL modm::log::DEBUG

PRETTYHOME_ENABLE_LOGGER(modm::platform::Usart1, modm::IOBuffer::BlockIfFull);

int
main()
{
	prettyhome::board::initialize();

	modm::platform::Usart1::connect< modm::platform::GpioA9::Tx >();
	modm::platform::Usart1::initialize< prettyhome::board::SystemClock, 115200_Bd >();

	modm::platform::Usart2::connect< modm::platform::GpioA2::Tx, modm::platform::GpioA3::Rx >();
	modm::platform::Usart2::initialize< prettyhome::board::SystemClock, 115200_Bd >();

	modm::platform::Can::connect< modm::platform::GpioA11::Rx, modm::platform::GpioA12::Tx > ();
	modm::platform::Can::initialize< prettyhome::board::SystemClock, 50_kbps > (0);

	prettyhome::System::initialize();

	prettyhome::interfaces::Interface *can = new prettyhome::interfaces::CanInterface< modm::platform::Can > ();
	can->initialize();

	prettyhome::interfaces::Interface *uart = new prettyhome::interfaces::UartInterface< modm::platform::Usart2 > ();
	uart->initialize();

	can->subscribeEvent(prettyhome::events::EventSelector(0x0000, 0x0000),
		[=](std::shared_ptr< prettyhome::events::Event > event) -> void
		{
			uart->reportEvent(event);
		}
	);

	do
	{
		can->run();
		uart->run();
	} while(true);

	return 0;
}
