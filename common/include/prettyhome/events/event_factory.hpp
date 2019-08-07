/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EVENT_FACTORY_HPP
#define PRETTYHOME_EVENT_FACTORY_HPP

#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace events
	{
		class EventFactory
		{
		public:
			/**
			 * @brief Make event.
			 * 
			 * @param type event type.
			 * @param data serialized event.
			 * @param callback event callback.
			 * @return std::shared_ptr< Event > constructed event or nullptr if event could not be made.
			 */
			static std::shared_ptr< Event >
			make(uint16_t type, std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);
		};
	}
}

#endif  // PRETTYHOME_EVENT_FACTORY_HPP
