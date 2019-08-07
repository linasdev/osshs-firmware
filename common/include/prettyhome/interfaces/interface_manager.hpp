/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_INTERFACE_MANAGER_HPP
#define PRETTYHOME_INTERFACE_MANAGER_HPP

#include <vector>
#include <memory>
#include <prettyhome/interfaces/interface.hpp>
#include <prettyhome/interfaces/event_packet.hpp>
#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		class InterfaceManager
		{
		public:
			/**
			 * @brief Initialize the interface manager.
			 * 
			 */
			static void
			initialize();

			/**
			 * @brief Register an interface.
			 * 
			 * @param interface interface to register.
			 */
			static void
			registerInterface(Interface *interface);

			/**
			 * @brief Report event packet. Should be called from within interfaces.
			 * 
			 * @param eventPacket event packet to report.
			 * @param sourceInterface pointer to the source interface.
			 */
			static void
			reportEventPacket(std::shared_ptr< EventPacket > eventPacket, Interface *sourceInterface = nullptr);

			/**
			 * @brief Report event. Should be called from System.
			 * 
			 * @param event event to report.
			 */
			static void
			reportEvent(std::shared_ptr< events::Event > event);

			/**
			 * @brief Update all registered interfaces.
			 * 
			 */
			static void
			run();
		private:
			static std::vector< Interface* > interfaces;
		};
	}
}

#endif  // PRETTYHOME_INTERFACE_MANAGER_HPP
