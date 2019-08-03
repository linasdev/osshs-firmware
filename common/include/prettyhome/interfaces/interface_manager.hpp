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
#include <prettyhome/modules/interface.hpp>
#include <prettyhome/events/event.hpp>
#include <prettyhome/events/event_selector.hpp>

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
			subscribeEvent(events::EventSelector selector);

			static void
			reportEvent(std::shared_ptr< events::Event > event);

			static bool
			run();
		private:
			static std::vector< Interface* > interfaces;
			static std::vector< events::EventSelector > eventSubscriptions;
		};
	}
}

#endif  // PRETTYHOME_INTERFACE_MANAGER_HPP