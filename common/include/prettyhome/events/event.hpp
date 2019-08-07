/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EVENT_HPP
#define PRETTYHOME_EVENT_HPP

#include <functional>
#include <memory>
#include <unordered_map>

namespace prettyhome
{
	namespace events
	{
		class Event;

		typedef std::function< void (std::shared_ptr< Event >) > EventCallback;

		class Event
		{
		public:
			static constexpr uint16_t CAUSE_ID_GENERATE = static_cast< uint16_t >(-1);

			/**
			 * @brief Construct event.
			 * 
			 * @param type event type id.
			 * @param causeId event cause id.
			 * @param callback event callback.
			 */
			Event(uint16_t type, uint16_t causeId = CAUSE_ID_GENERATE, EventCallback callback = nullptr);

			/**
			 * @brief Type id getter.
			 * 
			 * @return uint16_t event type id.
			 */
			uint16_t
			getType() const;

			/**
			 * @brief Cause id getter.
			 * 
			 * @return uint16_t event cause id.
			 */
			uint16_t
			getCauseId() const;

			/**
			 * @brief Callback getter.
			 * 
			 * @return EventCallback event callback.
			 */
			EventCallback
			getCallback() const;

			/**
			 * @brief Serialize this event.
			 * 
			 * @return std::unique_ptr< const uint8_t[] > serialized event or nullptr if serialization failed.
			 */
			virtual std::unique_ptr< const uint8_t[] >
			serialize() const = 0;
		protected:
			uint16_t causeId;
		private:
			typedef std::function< std::shared_ptr< Event > (std::unique_ptr< const uint8_t[] >, EventCallback) > EventMaker;
			static uint16_t nextCauseId;
			uint16_t type;
			EventCallback callback;

			Event(const Event&) = delete;

			Event&
			operator=(const Event&) = delete;

			static std::unordered_map< uint16_t, EventMaker >&
			eventRegister();

			template< typename DerivedEvent >
			friend class EventRegistrar;

			friend class EventFactory;
		};
	}
}
#endif  // PRETTYHOME_EVENT_HPP
