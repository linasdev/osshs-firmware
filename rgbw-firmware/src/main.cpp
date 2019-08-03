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
#include <prettyhome/interfaces/can_interface.hpp>
#include <prettyhome/modules/eeprom_module.hpp>
#include <prettyhome/modules/pwm_module.hpp>
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

	modm::platform::Can::connect< modm::platform::GpioA11::Rx, modm::platform::GpioA12::Tx > ();
	modm::platform::Can::initialize< prettyhome::board::SystemClock, 50_kbps > (0);

	modm::platform::I2cMaster1::connect< modm::platform::GpioB6::Scl, modm::platform::GpioB7::Sda >();
	modm::platform::I2cMaster1::initialize< prettyhome::board::SystemClock, 360_kBd >();

	modm::platform::SpiMaster1::connect< modm::platform::GpioA5::Sck, modm::platform::GpioA7::Mosi >();
	modm::platform::SpiMaster1::initialize< prettyhome::board::SystemClock, 1125_kBd >();

	PRETTYHOME_LOG_CLEAN();

	prettyhome::System::initialize();

	prettyhome::interfaces::Interface *can = new prettyhome::interfaces::CanInterface< modm::platform::Can > ();
	prettyhome::System::registerInterface(can);

	// std::shared_ptr< prettyhome::events::Event > event(new prettyhome::events::EepromRequestDataEvent(0x01, 0x02));
	// can->reportEvent(event);
	//
	// event.reset(new prettyhome::events::EepromUpdateSuccessEvent());
	// can->reportEvent(event);
	//
	// event.reset(new prettyhome::events::PwmRgbwChannelReadyEvent(0x00, prettyhome::events::PwmRgbwValue(0x01, 0x02, 0x03, 0x04)));
	// can->reportEvent(event);

	prettyhome::System::registerModule(
		new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >()
	);

	prettyhome::System::registerModule(
		new prettyhome::modules::PwmModule< 24, modm::platform::SpiMaster1, modm::platform::GpioA4, modm::platform::GpioA3 >()
	);

	prettyhome::System::loop();

	return 0;
}
