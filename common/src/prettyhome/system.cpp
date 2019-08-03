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

namespace prettyhome
{
	std::vector< modules::Module* > System::modules;
	std::unordered_map< events::EventSelector, std::vector< events::EventCallback > > System::eventSubscriptions;

	void
	System::initialize()
	{
		Time::initialize();
		InterfaceManager::initialize();
		InterfaceManager::subscribeEvent(events::EventSelector(0x0000, 0x0000));
	}

	void
	System::registerModule(modules::Module *module)
	{
		modules.push_back(module);
		module->initialize();
	}

	void
	System::subscribeEvent(events::EventSelector selector, events::EventCallback subscription)
	{
		eventSubscriptions[selector].push_back(subscription);
	}

	void
	System::reportEvent(std::shared_ptr< events::Event > event)
	{
		for(auto const &[selector, subscriptions] : eventSubscriptions)
			if (selector.match(event->getType()))
				for (auto const &subscription : subscriptions)
					subscription(event);
	}

	bool
	System::run()
	{

		PT_BEGIN();

		do
		{
			for (modules::Module *module : modules)
			{
				module->run();
			}

			PT_YIELD();
		}
		while (true);

		PT_END();
	}
}