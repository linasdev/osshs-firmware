/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EVENT_SELECTOR_HPP
#define PRETTYHOME_EVENT_SELECTOR_HPP

namespace prettyhome
{
	namespace events
	{
		typedef struct EventSelector
		{
			uint16_t mask;
			uint16_t identifier;

			EventSelector(uint16_t mask, uint16_t identifier)
			{
				this->mask = mask;
				this->identifier = identifier;
			}

			bool
			match(uint16_t type) const
			{
				return (type & mask) == identifier;
			}

			bool
			operator==(const EventSelector& rhs) const
			{
				return mask == rhs.mask && identifier == rhs.identifier;
			}
		} EventSelector;
	}
}

namespace std
{
	template<>
	struct hash< prettyhome::events::EventSelector >
	{
		size_t
		operator()(const prettyhome::events::EventSelector &eventSelector) const
		{
			return eventSelector.mask ^ eventSelector.identifier;
		}
	};
}

#endif  // PRETTYHOME_EVENT_SELECTOR_HPP
