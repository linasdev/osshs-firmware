/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_SYSTEM_HPP
#define PRETTYHOME_SYSTEM_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include <prettyhome/modules/module.hpp>
#include <prettyhome/events/event.hpp>
#include <prettyhome/events/event_selector.hpp>

namespace prettyhome
{
	class System
	{
	public:
		static void
		initialize();

		static void
		registerModule(modules::Module *module);

		static void
		subscribeEvent(events::EventSelector selector, events::EventCallback subscription);

		static void
		reportEvent(std::shared_ptr< events::Event > event);

		static void
		loop();
	private:
		static std::vector< modules::Module* > modules;
		static std::unordered_map< events::EventSelector, std::vector< events::EventCallback > > eventSubscriptions;
	};
}

#endif  // PRETTYHOME_SYSTEM_HPP