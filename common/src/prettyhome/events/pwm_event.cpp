/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/events/pwm_event.hpp>

namespace prettyhome
{
	namespace events
	{
		PwmStatus
		PwmStatusReadyEvent::getStatus() const
		{
			return status;
		}


		uint16_t
		PwmRequestChannelEvent::getChannel() const
		{
			return channel;
		}


		uint16_t
		PwmChannelReadyEvent::getChannel() const
		{
			return channel;
		}

		uint16_t
		PwmChannelReadyEvent::getValue() const
		{
			return value;
		}


		uint16_t
		PwmUpdateChannelEvent::getChannel() const
		{
			return channel;
		}

		uint16_t
		PwmUpdateChannelEvent::getValue() const
		{
			return value;
		}


		uint16_t
		PwmRequestRgbwChannelEvent::getChannel() const
		{
			return channel;
		}


		uint16_t
		PwmRgbwChannelReadyEvent::getChannel() const
		{
			return channel;
		}

		PwmRgbwValue
		PwmRgbwChannelReadyEvent::getValue() const
		{
			return value;
		}


		uint16_t
		PwmUpdateRgbwChannelEvent::getChannel() const
		{
			return channel;
		}

		PwmRgbwValue
		PwmUpdateRgbwChannelEvent::getValue() const
		{
			return value;
		}


		PwmError
		PwmErrorEvent::getError() const
		{
			return error;
		}
	}
}