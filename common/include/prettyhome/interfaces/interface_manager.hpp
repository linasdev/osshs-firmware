/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_INTERFACE_MANAGER_HPP
#define PRETTYHOME_INTERFACE_MANAGER_HPP

#include <vector>
#include <memory>
#include <modm/processing/protothread.hpp>
#include <prettyhome/interfaces/interface.hpp>
#include <prettyhome/interfaces/event_packet.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		class InterfaceManager : public modm::pt::Protothread
		{
		public:
			static void
			initialize();

			static void
			registerInterface(Interface *interface);

			static void
			reportEventPacket(std::shared_ptr< EventPacket > eventPacket, Interface *sourceInterface = nullptr);

			static bool
			run();
		private:
			static std::vector< Interface* > interfaces;
		};
	}
}

#endif  // PRETTYHOME_INTERFACE_MANAGER_HPP