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

namespace prettyhome
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
    match(Event &event) const
    {
      return (event.getType() & mask) == identifier;
    }

    bool
    operator==(const EventSelector& rhs) const
    {
      return mask == rhs.mask && identifier == rhs.identifier;
    }
  } EventSelector;

	typedef std::function< void (Event&) > EventSubscription;
}

namespace std
{
  template<>
  struct hash< prettyhome::EventSelector >
  {
    size_t
    operator()(const prettyhome::EventSelector &eventSelector) const
    {
      return eventSelector.mask ^ eventSelector.identifier;
    }
  };
}

#endif  // PRETTYHOME_EVENT_HPP