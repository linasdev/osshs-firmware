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

#ifndef OSSHS_SYSTEM_HPP
#define OSSHS_SYSTEM_HPP

#include <osshs/protocol/interfaces/interface.hpp>
#include <osshs/modules/module.hpp>
#include <osshs/events/event_selector.hpp>

namespace osshs
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
		registerInterface(protocol::interfaces::Interface *interface);

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

#endif  // OSSHS_SYSTEM_HPP
