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

namespace prettyhome
{
	namespace events
	{
		class Event;
		typedef std::function< void (std::shared_ptr< Event >) > EventCallback;

		class Event
		{
		public:
			enum
			{
				FORM_CHANNEL_EVENT = 0x0000
			};

			Event(uint16_t type, EventCallback callback = nullptr, bool formChannel = false)
				: type(type), causeId(nextCauseId++), callback(callback), formChannel(formChannel)
			{
			}

			Event(uint16_t type, uint16_t causeId, EventCallback callback = nullptr, bool formChannel = false)
				: type(type), causeId(causeId), callback(callback), formChannel(formChannel)
			{
			}

			uint16_t
			getType() const;

			uint16_t
			getCauseId() const;

			EventCallback
			getCallback() const;

			bool
			shouldFormChannel() const;
		private:
			uint16_t type;
			uint16_t causeId;
			static uint16_t nextCauseId;
			EventCallback callback;
			bool formChannel;

			Event(const Event&) = delete;

			Event&
			operator=(const Event&) = delete;
		};
	}
}
#endif  // PRETTYHOME_EVENT_HPP