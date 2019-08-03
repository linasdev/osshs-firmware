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
	#error "Don't include this file directly, use 'uart_interface.hpp' instead!"
#endif

#include <modm/platform.hpp>
#include <prettyhome/resource_lock.hpp>
#include <prettyhome/log/logger.hpp>

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

				PT_CALL(writeEventPacket(currentEventPacket));

				currentEventPacket.reset();
			}
			while (true);

			PT_END();
		}

		template< typename Uart >
		void
		UartInterface< Uart >::initialize()
		{
			PRETTYHOME_LOG_INFO("Initializing UART interface.");
		}

		template< typename Uart >
		modm::ResumableResult<void>
		UartInterface< Uart >::writeEventPacket(std::shared_ptr< EventPacket > eventPacket)
		{
			RF_BEGIN();

			PRETTYHOME_LOG_DEBUG_STREAM << "Writing event packet"
				<< "(multi_target = "<< eventPacket->isMultiTarget()
				<< ", command = " << eventPacket->isCommand()
				<< ", transmitter_mac = " << eventPacket->getTransmitterMac()
				<< ", receiver_mac = " << eventPacket->getTransmitterMac()
				<< ", event_type = " << eventPacket->getEvent()->getType()
				<< ").\r\n";

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
