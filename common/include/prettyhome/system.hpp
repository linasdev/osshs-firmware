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

#include <prettyhome/modules/module.hpp>
#include <prettyhome/event.hpp>

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
		subscribeEvent(EventSelector selector, EventSubscription subscription);

		static void
		reportEvent(Event &event);
	private:
		static std::vector< modules::Module* > modules;
		static std::unordered_map< EventSelector, std::vector< EventSubscription > > eventSubscriptions;
	};
}

#endif  // PRETTYHOME_SYSTEM_HPP