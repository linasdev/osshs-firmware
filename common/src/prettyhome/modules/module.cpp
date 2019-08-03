/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/modules/module.hpp>
#include <prettyhome/system.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	namespace modules
	{
		void
		Module::initialize()
		{
			PRETTYHOME_LOG_INFO("Initializing module.");

			System::subscribeEvent(events::EventSelector(0xff00, static_cast< uint16_t >(getModuleTypeId()) << 8),
				[=](std::shared_ptr< events::Event > event) -> void
				{
					this->handleEvent(event);
				}
			);
		}

		void
		Module::handleEvent(std::shared_ptr< events::Event > event)
		{
			PRETTYHOME_LOG_DEBUG_STREAM << "Handling event(type = " << event->getType() << ").\r\n";

			eventQueue.push(event);
		}
	}
}