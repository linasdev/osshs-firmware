/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_UART_INTERFACE_HPP
  #error	"Don't include this file directly, use 'uart_interface.hpp' instead!"
#endif

#include <modm/platform.hpp>
#include <prettyhome/resource_lock.hpp>
#include <prettyhome/events/event_factory.hpp>

namespace prettyhome
{
	namespace interfaces
	{
    template< typename Uart >
		bool
		UartInterface< Uart >::run()
		{
			PT_BEGIN();

			do
			{
				PT_WAIT_WHILE(eventPacketQueue.empty());

				currentEventPacket = eventPacketQueue.front();
				eventPacketQueue.pop();

				PT_CALL(transferEventPacket(currentEventPacket));

				currentEventPacket.reset();
			}
			while (true);

			PT_END();
		}

    template< typename Uart >
    void
    UartInterface< Uart >::initialize()
    {
    }

    template< typename Uart >
    modm::ResumableResult<void>
    UartInterface< Uart >::transferEventPacket(std::shared_ptr< events::EventPacket > eventPacket)
    {
      RF_BEGIN();

  		RF_WAIT_UNTIL(ResourceLock< Uart >::tryLock());

      {
        std::unique_ptr< const uint8_t[] > buffer = eventPacket->serialize();
        uint16_t bufferLength = buffer[0] | (buffer[1] << 8);

        Uart::writeBlocking(buffer.get(), bufferLength);
      }

  		ResourceLock< Uart >::unlock();

      RF_END();
    }
	}
}
