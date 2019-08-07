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

#include <prettyhome/interfaces/interface.hpp>
#include <prettyhome/modules/module.hpp>
#include <prettyhome/events/event_selector.hpp>

namespace prettyhome
{
	class System
	{
	public:
		/**
		 * @brief Initialize system.
		 * 
		 */
		static void
		initialize();

		/**
		 * @brief Register an interface to InterfaceManager.
		 * 
		 * @param interface interface to register.
		 */
		static void
		registerInterface(interfaces::Interface *interface);

		/**
		 * @brief Register a module to ModuleManager.
		 * 
		 * @param module module to register.
		 */
		static void
		registerModule(modules::Module *module);

		/**
		 * @brief Subscribe to events based on their type id.
		 * 
		 * @param selector event selector consisting of a mask and an identifier.
		 * @param subscription callback to call when event matching the selector is reported.
		 */
		static void
		subscribeEvent(events::EventSelector selector, events::EventCallback subscription);

		/**
		 * @brief Report event to system.
		 * 
		 * @param event event to report.
		 */
		static void
		reportEvent(std::shared_ptr< events::Event > event);

		/**
		 * @brief Enter main system loop. Does not return.
		 * 
		 */
		static void
		loop();
	private:
		static std::unordered_map< events::EventSelector, std::vector< events::EventCallback > > eventSubscriptions;
	};
}

#endif  // PRETTYHOME_SYSTEM_HPP
