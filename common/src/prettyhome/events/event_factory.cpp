/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/events/event_factory.hpp>

namespace prettyhome
{
	namespace events
	{
		std::shared_ptr< Event >
		EventFactory::make(uint16_t type, std::unique_ptr< const uint8_t[] > data, EventCallback callback)
		{
			return Event::eventRegister().at(type)(std::move(data), callback);
		}
	}
}