/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

 #include <prettyhome/interface/interface_manager.hpp>
 #include <prettyhome/interface/system.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		std::vector< Interface* > InterfaceManager::interfaces;
		std::vector< events::EventSelector > InterfaceManager::eventSubscriptions;

		void
		InterfaceManager::initialize()
		{
		}

		void
		InterfaceManager::registerInterface(Interface *interface)
		{
			interfaces.push_back(interface);
			interface->initialize();
		}

		void
		InterfaceManager::subscribeEvent(events::EventSelector selector)
		{
			eventSubscriptions.push_back(selector);
		}

		void
		InterfaceManager::reportEvent(std::shared_ptr< events::Event > event)
		{
			for(auto const selector : eventSubscriptions)
				if (selector.match(event->getType()))
					System::reportEvent(event);
		}

		bool
		InterfaceManager::run()
		{
			PT_BEGIN();

			do
			{
				for (Interface *interface : interfaces)
				{
					interface->run();
				}

				PT_YIELD();
			}
			while (true);

			PT_END();
		}
	}
}