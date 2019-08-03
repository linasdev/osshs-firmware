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

#include <cstdint>
#include <queue>
#include <modm/processing/protothread.hpp>
#include <modm/processing/resumable.hpp>
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

			virtual bool
			run() = 0;

			void
			reportEventPacket(std::shared_ptr< EventPacket > eventPacket);
		private:
			Interface(const Interface&) = delete;

			Interface&
			operator=(const Interface&) = delete;

			virtual void
			initialize() = 0;

			friend InterfaceManager;
		};
	}
}

#endif  // PRETTYHOME_INTERFACE_HPP
