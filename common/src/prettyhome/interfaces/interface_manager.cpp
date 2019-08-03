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