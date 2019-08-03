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
#define PRETTYHOME_UART_INTERFACE_HPP

#include <prettyhome/interfaces/interface.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		template< typename Uart >
		class UartInterface : public Interface, private modm::NestedResumable<1>
		{
		public:
			UartInterface() = default;
		protected:
			bool
			run();
		private:
			std::shared_ptr< EventPacket > currentEventPacket;

			void
			initialize();

			modm::ResumableResult<void>
			writeEventPacket(std::shared_ptr< EventPacket > eventPacket);
	  };
	}
}

#include <prettyhome/interfaces/uart_interface_impl.hpp>

#endif  // PRETTYHOME_UART_INTERFACE_HPP
