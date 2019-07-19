/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/interfaces/interface.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		void
		Interface::subscribeEvent(events::EventSelector selector, events::EventCallback subscription)
		{
			eventSubscriptions[selector].push_back(subscription);
		}

		void
		Interface::reportEvent(std::shared_ptr< events::Event > event)
		{
			eventQueue.push(event);
		}
	}
}