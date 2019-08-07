/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_INTERFACE_HPP
#define PRETTYHOME_INTERFACE_HPP

#include <queue>
#include <modm/processing/protothread.hpp>
#include <prettyhome/interfaces/event_packet.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		class InterfaceManager;

		class Interface : public modm::pt::Protothread
		{
		public:
			Interface() = default;
		protected:
			std::queue< std::shared_ptr< EventPacket > > eventPacketQueue;

			/**
			 * @brief Run interface protothread.
			 * 
			 */
			virtual bool
			run() = 0;

			/**
			 * @brief Report an event packet to be transmitted.
			 * 
			 * @param eventPacket event packet to transmit.
			 */
			void
			reportEventPacket(std::shared_ptr< EventPacket > eventPacket);
		private:
			Interface(const Interface&) = delete;

			Interface&
			operator=(const Interface&) = delete;

			/**
			 * @brief Initialize the interface. Should only be called from InterfaceManager.
			 * 
			 */
			virtual void
			initialize() = 0;

			friend InterfaceManager;
		};
	}
}

#endif  // PRETTYHOME_INTERFACE_HPP
