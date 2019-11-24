/*
 * MIT License
 *
 * Copyright (c) 2019 Linas Nikiperavicius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <osshs/system.hpp>
#include <osshs/interfaces/can_interface.hpp>
#include <osshs/modules/eeprom_module.hpp>
#include <osshs/modules/pwm_module.hpp>
#include <osshs/log/logger.hpp>

#include "./board.hpp"

using namespace modm::literals;

#undef	MODM_LOG_LEVEL
#define	MODM_LOG_LEVEL modm::log::DEBUG

OSSHS_ENABLE_LOGGER(modm::platform::Usart1, modm::IOBuffer::BlockIfFull);

int
main()
{
	osshs::board::initialize();

	modm::platform::Usart1::connect< modm::platform::GpioA9::Tx >();
	modm::platform::Usart1::initialize< osshs::board::SystemClock, 115200_Bd >();

	modm::platform::Can::connect< modm::platform::GpioA11::Rx, modm::platform::GpioA12::Tx > ();
	modm::platform::Can::initialize< osshs::board::SystemClock, 50_kbps > (0);

	modm::platform::I2cMaster1::connect< modm::platform::GpioB6::Scl, modm::platform::GpioB7::Sda >();
	modm::platform::I2cMaster1::initialize< osshs::board::SystemClock, 360_kBd >();

	modm::platform::SpiMaster1::connect< modm::platform::GpioA5::Sck, modm::platform::GpioA7::Mosi >();
	modm::platform::SpiMaster1::initialize< osshs::board::SystemClock, 1125_kBd >();

	OSSHS_LOG_CLEAN();

	osshs::System::initialize();

	osshs::System::registerInterface(
		new osshs::interfaces::CanInterface< modm::platform::Can > ()
	);

	std::shared_ptr< osshs::events::Event > event(new osshs::events::EepromRequestDataEvent(0x01, 0x02));
	osshs::interfaces::InterfaceManager::reportEvent(event);

	event.reset(new osshs::events::EepromUpdateSuccessEvent());
	osshs::interfaces::InterfaceManager::reportEvent(event);

	event.reset(new osshs::events::PwmRgbwChannelReadyEvent(0x00, osshs::events::PwmRgbwValue(0x01, 0x02, 0x03, 0x04)));
	osshs::interfaces::InterfaceManager::reportEvent(event);

	osshs::System::registerModule(
		new osshs::modules::EepromModule< modm::platform::I2cMaster1 >()
	);

	osshs::System::registerModule(
		new osshs::modules::PwmModule< 24, modm::platform::SpiMaster1, modm::platform::GpioA4, modm::platform::GpioA3 >()
	);

	osshs::System::loop();

	return 0;
}
