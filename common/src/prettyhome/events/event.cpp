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
		uint16_t Event::nextCauseId = 0;

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

		uint8_t*
		Event::getData() const
		{
			return data;
		}

		size_t
		Event::getDataLen() const
		{
			return dataLen;
		}

		EventCallback
		Event::getCallback() const
		{
			return callback;
		}

		bool
		Event::shouldFormChannel() const
		{
			return formChannel;
		}
	}
}