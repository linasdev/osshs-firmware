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
#include <osshs/protocol/interfaces/uart_interface.hpp>
#include <osshs/protocol/interfaces/can_interface.hpp>
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

	modm::platform::Usart1::connect<modm::platform::GpioA9::Tx>();
	modm::platform::Usart1::initialize<osshs::board::SystemClock, 115200_Bd>();

	modm::platform::Usart2::connect<modm::platform::GpioA2::Tx, modm::platform::GpioA3::Rx>();
	modm::platform::Usart2::initialize<osshs::board::SystemClock, 115200_Bd>();

	modm::platform::Can::connect<modm::platform::GpioA11::Rx, modm::platform::GpioA12::Tx> ();
	modm::platform::Can::initialize<osshs::board::SystemClock, 50_kbps>(0);

	osshs::System::initialize();

	osshs::System::registerInterface(
		new osshs::protocol::interfaces::UartInterface<modm::platform::Usart2>()
	);

	osshs::System::registerInterface(
		new osshs::protocol::interfaces::CanInterface<modm::platform::Can>()
	);

	osshs::System::loop();

	return 0;
}
