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
#include <prettyhome/modules/eeprom_module.hpp>

#include "./board.hpp"

using namespace modm::literals;

#undef	MODM_LOG_LEVEL
#define	MODM_LOG_LEVEL modm::log::DEBUG

PRETTYHOME_ENABLE_LOGGER(modm::platform::Usart1, modm::IOBuffer::BlockIfFull);

int
main()
{
	prettyhome::board::initialize();

	modm::platform::Usart1::connect<modm::platform::GpioOutputA9::Tx>();
	modm::platform::Usart1::initialize<prettyhome::board::SystemClock, 115200_Bd>();

	PRETTYHOME_LOG_CLEAN();

	prettyhome::System::initialize();
	prettyhome::System::registerModule(new prettyhome::modules::EepromModule());
	
	do
	{
	} while (true);

	return 0;
}