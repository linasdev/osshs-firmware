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
		std::unique_ptr< const uint8_t[] >
		PwmRequestStatusEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 4;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmStatus
		PwmStatusReadyEvent::getStatus() const
		{
			return status;
		}

		std::unique_ptr< const uint8_t[] >
		PwmStatusReadyEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 5;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = static_cast< uint8_t >(status);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		std::unique_ptr< const uint8_t[] >
		PwmEnableEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 4;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		std::unique_ptr< const uint8_t[] >
		PwmDisableEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 4;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		uint16_t
		PwmRequestChannelEvent::getChannel() const
		{
			return channel;
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestChannelEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 6;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
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

		std::unique_ptr< const uint8_t[] >
		PwmChannelReadyEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 8;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			buffer[6] = value & 0xff;
			buffer[7] = (value >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
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

		std::unique_ptr< const uint8_t[] >
		PwmUpdateChannelEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 8;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			buffer[6] = value & 0xff;
			buffer[7] = (value >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		uint16_t
		PwmRequestRgbwChannelEvent::getChannel() const
		{
			return channel;
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestRgbwChannelEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 6;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
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

		std::unique_ptr< const uint8_t[] >
		PwmRgbwChannelReadyEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 14;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			buffer[6] = value.red & 0xff;
			buffer[7] = (value.red >> 8);

			buffer[8] = value.green & 0xff;
			buffer[9] = (value.green >> 8);

			buffer[10] = value.blue & 0xff;
			buffer[11] = (value.blue >> 8);

			buffer[12] = value.white & 0xff;
			buffer[13] = (value.white >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
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

		std::unique_ptr< const uint8_t[] >
		PwmUpdateRgbwChannelEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 14;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			buffer[6] = value.red & 0xff;
			buffer[7] = (value.red >> 8);

			buffer[8] = value.green & 0xff;
			buffer[9] = (value.green >> 8);

			buffer[10] = value.blue & 0xff;
			buffer[11] = (value.blue >> 8);

			buffer[12] = value.white & 0xff;
			buffer[13] = (value.white >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		std::unique_ptr< const uint8_t[] >
		PwmUpdateSuccessEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 4;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmError
		PwmErrorEvent::getError() const
		{
			return error;
		}

		std::unique_ptr< const uint8_t[] >
		PwmErrorEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 5;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = static_cast< uint8_t >(error);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}
	}
}