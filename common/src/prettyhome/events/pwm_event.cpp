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
		PwmRequestStatusEvent::PwmRequestStatusEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmRequestStatusEvent>(causeId, callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestStatusEvent::serialize() const
		{
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmStatusReadyEvent::PwmStatusReadyEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmStatusReadyEvent>(causeId, callback)
		{
			status = static_cast< PwmStatus >(data[4]);
		}

		PwmStatus
		PwmStatusReadyEvent::getStatus() const
		{
			return status;
		}

		std::unique_ptr< const uint8_t[] >
		PwmStatusReadyEvent::serialize() const
		{
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = static_cast< uint8_t >(status);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmEnableEvent::PwmEnableEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmEnableEvent>(causeId, callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmEnableEvent::serialize() const
		{
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmDisableEvent::PwmDisableEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmDisableEvent>(causeId, callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmDisableEvent::serialize() const
		{
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmRequestChannelEvent::PwmRequestChannelEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmRequestChannelEvent>(causeId, callback)
		{
			channel = data[4] | (data[5] << 8);
		}

		uint16_t
		PwmRequestChannelEvent::getChannel() const
		{
			return channel;
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestChannelEvent::serialize() const
		{
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmChannelReadyEvent::PwmChannelReadyEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmChannelReadyEvent>(causeId, callback)
		{
			channel = data[4] | (data[5] << 8);
			value = data[6] | (data[7] << 8);
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


		PwmUpdateChannelEvent::PwmUpdateChannelEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmUpdateChannelEvent>(causeId, callback)
		{
			channel = data[4] | (data[5] << 8);
			value = data[6] | (data[7] << 8);
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


		PwmRequestRgbwChannelEvent::PwmRequestRgbwChannelEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmRequestRgbwChannelEvent>(causeId, callback)
		{
			channel = data[4] | (data[5] << 8);
		}

		uint16_t
		PwmRequestRgbwChannelEvent::getChannel() const
		{
			return channel;
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestRgbwChannelEvent::serialize() const
		{
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = channel & 0xff;
			buffer[5] = (channel >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmRgbwChannelReadyEvent::PwmRgbwChannelReadyEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmRgbwChannelReadyEvent>(causeId, callback)
		{
			channel = data[4] | (data[5] << 8);
			value.red = data[6] | (data[7] << 8);
			value.green = data[8] | (data[9] << 8);
			value.blue = data[10] | (data[11] << 8);
			value.white = data[12] | (data[13] << 8);
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


		PwmUpdateRgbwChannelEvent::PwmUpdateRgbwChannelEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmUpdateRgbwChannelEvent>(causeId, callback)
		{
			channel = data[4] | (data[5] << 8);
			value.red = data[6] | (data[7] << 8);
			value.green = data[8] | (data[9] << 8);
			value.blue = data[10] | (data[11] << 8);
			value.white = data[12] | (data[13] << 8);
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


		PwmUpdateSuccessEvent::PwmUpdateSuccessEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmUpdateSuccessEvent>(causeId, callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmUpdateSuccessEvent::serialize() const
		{
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmErrorEvent::PwmErrorEvent(std::unique_ptr< const uint8_t[] > data, uint16_t causeId, EventCallback callback)
			: EventRegistrar<PwmErrorEvent>(causeId, callback)
		{
			error = static_cast< PwmError >(data[4]);
		}

		PwmError
		PwmErrorEvent::getError() const
		{
			return error;
		}

		std::unique_ptr< const uint8_t[] >
		PwmErrorEvent::serialize() const
		{
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