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
  #error	"Don't include this file directly, use 'event_registrar.hpp' instead!"
#endif

namespace prettyhome
{
	namespace events
	{
		template< typename DerivedEvent >
		bool EventRegistrar< DerivedEvent >::registered = EventRegistrar< DerivedEvent >::registerDerivedEvent();

		template< typename DerivedEvent >
		bool
		EventRegistrar< DerivedEvent >::registerDerivedEvent()
		{
			Event::eventRegister()[DerivedEvent::TYPE] =
				[](std::unique_ptr< const uint8_t[] > data, EventCallback callback) -> std::shared_ptr< Event >
			{
				return std::make_shared< DerivedEvent >(std::move(data), callback);
			};

			return true;
		}

		template< typename DerivedEvent >
		EventRegistrar< DerivedEvent >::EventRegistrar(uint16_t causeId, EventCallback callback)
			: Event(DerivedEvent::TYPE, causeId, callback)
		{
			static_cast< void >(registered);
		}
	}
}