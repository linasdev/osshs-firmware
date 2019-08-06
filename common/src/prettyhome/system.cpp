/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/system.hpp>
#include <prettyhome/time.hpp>
#include <prettyhome/interfaces/interface_manager.hpp>
#include <prettyhome/modules/module_manager.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	std::unordered_map< events::EventSelector, std::vector< events::EventCallback > > System::eventSubscriptions;

	void
	System::initialize()
	{
		PRETTYHOME_LOG_INFO("Initializing system.");

		Time::initialize();
		interfaces::InterfaceManager::initialize();
		modules::ModuleManager::initialize();
	}

	void
	System::registerInterface(interfaces::Interface *interface)
	{
		PRETTYHOME_LOG_INFO("Registering interface.");

		interfaces::InterfaceManager::registerInterface(interface);
	}

	void
	System::registerModule(modules::Module *module)
	{
		PRETTYHOME_LOG_INFO_STREAM << "Registering module(type = " << module->getModuleTypeId() << ").\r\n";

		modules::ModuleManager::registerModule(module);
	}

	void
	System::subscribeEvent(events::EventSelector selector, events::EventCallback subscription)
	{
		PRETTYHOME_LOG_INFO_STREAM << "Subscribing to event(mask = " << selector.mask << ", identifier = " << selector.identifier << ").\r\n";

		eventSubscriptions[selector].push_back(subscription);
	}

	void
	System::reportEvent(std::shared_ptr< events::Event > event)
	{
		PRETTYHOME_LOG_DEBUG_STREAM << "Handling event(type = " << event->getType() << ").\r\n";
		
		for(auto const &[selector, subscriptions] : eventSubscriptions)
			if (selector.match(event->getType()))
				for (auto const &subscription : subscriptions)
					subscription(event);
	}

	void
	System::loop()
	{
		do
		{
			interfaces::InterfaceManager::run();
			modules::ModuleManager::run();
		}
		while (true);
	}
}
