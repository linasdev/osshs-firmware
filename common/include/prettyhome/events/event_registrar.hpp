/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EVENT_REGISTRAR_HPP
#define PRETTYHOME_EVENT_REGISTRAR_HPP

#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace events
	{
		template< typename DerivedEvent >
		class EventRegistrar : public Event
		{
		public:
			static bool registered;

			static bool
			registerDerivedEvent();
		private:
			EventRegistrar(uint16_t causeId, EventCallback callback);

			friend DerivedEvent;
		};
	}
}

#include <prettyhome/events/event_registrar_impl.hpp>

#endif  // PRETTYHOME_EVENT_REGISTRAR_HPP