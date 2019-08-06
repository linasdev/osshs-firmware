/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/system.hpp>
#include <prettyhome/interfaces/uart_interface.hpp>
#include <prettyhome/interfaces/can_interface.hpp>
#include <prettyhome/log/logger.hpp>

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

	PRETTYHOME_LOG_CLEAN();

	prettyhome::System::initialize();

	prettyhome::System::registerInterface(
		new prettyhome::interfaces::UartInterface< modm::platform::Usart2 > ()
	);

	prettyhome::System::registerInterface(
		new prettyhome::interfaces::CanInterface< modm::platform::Can > ()
	);

	prettyhome::System::loop();

	return 0;
}