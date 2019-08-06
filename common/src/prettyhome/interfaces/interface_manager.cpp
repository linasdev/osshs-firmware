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
#include <prettyhome/system.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		std::vector< Interface* > InterfaceManager::interfaces;

		void
		InterfaceManager::initialize()
		{
			PRETTYHOME_LOG_INFO("Initializing interface manager.");
		}

		void
		InterfaceManager::registerInterface(Interface *interface)
		{
			PRETTYHOME_LOG_INFO("Registering interface.");

			interfaces.push_back(interface);
			interface->initialize();
		}

		void
		InterfaceManager::reportEventPacket(std::shared_ptr< EventPacket > eventPacket, Interface *sourceInterface)
		{
			PRETTYHOME_LOG_DEBUG_STREAM << "Handling event packet"
				<< "(multi_target = "<< eventPacket->isMultiTarget()
				<< ", command = " << eventPacket->isCommand()
				<< ", transmitter_mac = " << eventPacket->getTransmitterMac()
				<< ", receiver_mac = " << eventPacket->getTransmitterMac()
				<< ", event_type = " << eventPacket->getEvent()->getType()
				<< ").\r\n";

			if (eventPacket->isMalformed())
			{
				PRETTYHOME_LOG_WARNING("Discarding malformed event packet.");
				return;
			}

			for (Interface *interface : interfaces)
			{
				if (interface == sourceInterface)
					continue;
					
				interface->reportEventPacket(eventPacket);
			}

			System::reportEvent(eventPacket->getEvent());
		}

		void
		InterfaceManager::reportEvent(std::shared_ptr< events::Event > event)
		{
			PRETTYHOME_LOG_DEBUG_STREAM << "Handling event(type = " << event->getType() << ").\r\n";

			std::shared_ptr< EventPacket > eventPacket(new EventPacket(
				event,
				0x00000000
			));

			if (eventPacket->isMalformed())
			{
				PRETTYHOME_LOG_WARNING("Discarding malformed event packet.");
				return;
			}

			for (Interface *interface : interfaces)
			{
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
