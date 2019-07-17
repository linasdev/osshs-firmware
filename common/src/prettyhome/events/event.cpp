/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace events
	{
		// std::unordered_map< uint16_t, Event::EventMaker > Event::eventRegister;
		uint16_t Event::nextCauseId = 0;

		Event::Event(uint16_t type, uint16_t causeId, EventCallback callback)
		 	: type(type), callback(callback)
		{
			this->causeId = (causeId == CAUSE_ID_GENERATE) ? nextCauseId++ : causeId;

			if (nextCauseId == CAUSE_ID_GENERATE)
			{
				nextCauseId++;
			}
		}

		uint16_t
		Event::getType() const
		{
			return type;
		}

		uint16_t
		Event::getCauseId() const
		{
			return causeId;
		}

		EventCallback
		Event::getCallback() const
		{
			return callback;
		}

		std::unordered_map< uint16_t, Event::EventMaker >&
		Event::eventRegister()
		{
			static std::unordered_map< uint16_t, Event::EventMaker > map;
			return map;
		}
	}
}