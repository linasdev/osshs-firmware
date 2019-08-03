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
		uint8_t
		UartInterface< Uart >::getInterfaceTypeId() const
		{
			return UART_INTERFACE_ID;
		}

    template< typename Uart >
		bool
		UartInterface< Uart >::run()
		{
			PT_BEGIN();

			do
			{
				PT_WAIT_WHILE(eventQueue.empty());

				currentEvent = eventQueue.front();
				eventQueue.pop();

				PT_CALL(transferEvent(currentEvent));

				currentEvent.reset();

    		PT_WAIT_UNTIL(ResourceLock< Uart >::tryLock());

        {
          uint8_t byte0 = 0x00;
          uint8_t byte1 = 0x00;

          if (Uart::read(byte0))
          {
            if (Uart::read(byte1))
            {
              uint16_t bufferLength = byte0 | (byte1 << 8);
              uint8_t *buffer = new uint8_t[bufferLength];

              buffer[0] = byte0;
              buffer[1] = byte1;

              for (uint16_t i = 2; i < bufferLength; i++)
              {
                uint8_t temp = 0x00;

                while(!Uart::read(temp));

                buffer[i] = temp;
              }

              uint16_t eventType = buffer[2] | (buffer[3] << 8);

              std::shared_ptr< events::Event > event = events::EventFactory::make(eventType, std::unique_ptr< const uint8_t[] >(buffer), events::Event::CAUSE_ID_GENERATE,
      					[=](std::shared_ptr< events::Event > event) -> void
      					{
      							this->reportEvent(event);
      					}
              );

							System::reportEvent(event);
            }
          }
        }

    		ResourceLock< Uart >::unlock();
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
    UartInterface< Uart >::transferEvent(std::shared_ptr< events::Event > event)
    {
      RF_BEGIN();

  		RF_WAIT_UNTIL(ResourceLock< Uart >::tryLock());

      {
        std::unique_ptr< const uint8_t[] > buffer = event->serialize();
        uint16_t bufferLength = buffer[0] | (buffer[1] << 8);

        Uart::writeBlocking(buffer.get(), bufferLength);
      }

  		ResourceLock< Uart >::unlock();

      RF_END();
    }
	}
}
