/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

 #include <prettyhome/interfaces/interface_manager.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		std::vector< Interface* > InterfaceManager::interfaces;

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
		InterfaceManager::reportEventPacket(std::shared_ptr< EventPacket > eventPacket, Interface *sourceInterface)
		{
			for (Interface *interface : interfaces)
			{
				if (interface == sourceInterface)
					continue;

				interface->reportEventPacket(eventPacket);
			}
		}

		void
		InterfaceManager::run()
		{
			for (Interface *interface : interfaces)
			{
				interface->run();
			}
		}
	}
}