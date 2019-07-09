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

namespace prettyhome
{
	namespace events
	{
		class Event
		{
		public:
			Event(uint16_t type) : type(type)
			{
			};

			uint16_t
			getType() const;
		private:
			uint16_t type;

			Event(const Event&) = delete;

			Event&
			operator=(const Event&) = delete;
		};

		typedef std::function< void (Event&) > EventCallback;
	}
}
#endif  // PRETTYHOME_EVENT_HPP