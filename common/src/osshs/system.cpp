/*
 * MIT License
 *
 * Copyright (c) 2019 Linas Nikiperavicius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <osshs/system.hpp>
#include <osshs/time.hpp>
#include <osshs/interfaces/interface_manager.hpp>
#include <osshs/modules/module_manager.hpp>
#include <osshs/log/logger.hpp>

namespace osshs
{
	std::unordered_map< events::EventSelector, std::vector< events::EventCallback > > System::eventSubscriptions;

	void
	System::initialize()
	{
		OSSHS_LOG_INFO("Initializing system.");

		Time::initialize();
		interfaces::InterfaceManager::initialize();
		modules::ModuleManager::initialize();
	}

	void
	System::registerInterface(interfaces::Interface *interface)
	{
		OSSHS_LOG_INFO("Registering interface.");

		interfaces::InterfaceManager::registerInterface(interface);
	}

	void
	System::registerModule(modules::Module *module)
	{
		OSSHS_LOG_INFO_STREAM << "Registering module(type = " << module->getModuleTypeId() << ").\r\n";

		modules::ModuleManager::registerModule(module);
	}

	void
	System::subscribeEvent(events::EventSelector selector, events::EventCallback subscription)
	{
		OSSHS_LOG_INFO_STREAM << "Subscribing to event(mask = " << selector.mask << ", identifier = " << selector.identifier << ").\r\n";

		eventSubscriptions[selector].push_back(subscription);
	}

	void
	System::reportEvent(std::shared_ptr< events::Event > event)
	{
		OSSHS_LOG_DEBUG_STREAM << "Handling event(type = " << event->getType() << ").\r\n";
		
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
			modules::ModuleManager::update();
		}
		while (true);
	}
}
