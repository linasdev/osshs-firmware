/*
 * MIT License
 *
 * Copyright (c) 2019 Linas Nikiperavicius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <osshs/events/pwm_event.hpp>
#include <osshs/log/logger.hpp>

namespace osshs
{
	namespace events
	{
		PwmRequestStatusEvent::PwmRequestStatusEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmRequestStatusEvent>(data[4] | (data[5] << 8), callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestStatusEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmStatusReadyEvent::PwmStatusReadyEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmStatusReadyEvent>(data[4] | (data[5] << 8), callback)
		{
			status = static_cast< PwmStatus >(data[6]);
		}

		PwmStatus
		PwmStatusReadyEvent::getStatus() const
		{
			return status;
		}

		std::unique_ptr< const uint8_t[] >
		PwmStatusReadyEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = static_cast< uint8_t >(status);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmEnableEvent::PwmEnableEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmEnableEvent>(data[4] | (data[5] << 8), callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmEnableEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmDisableEvent::PwmDisableEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmDisableEvent>(data[4] | (data[5] << 8), callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmDisableEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmRequestChannelEvent::PwmRequestChannelEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmRequestChannelEvent>(data[4] | (data[5] << 8), callback)
		{
			channel = data[6] | (data[7] << 8);
		}

		uint16_t
		PwmRequestChannelEvent::getChannel() const
		{
			return channel;
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestChannelEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = channel & 0xff;
			buffer[7] = (channel >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmChannelReadyEvent::PwmChannelReadyEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmChannelReadyEvent>(data[4] | (data[5] << 8), callback)
		{
			channel = data[6] | (data[7] << 8);
			value = data[8] | (data[9] << 8);
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
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = channel & 0xff;
			buffer[7] = (channel >> 8);

			buffer[8] = value & 0xff;
			buffer[9] = (value >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmUpdateChannelEvent::PwmUpdateChannelEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmUpdateChannelEvent>(data[4] | (data[5] << 8), callback)
		{
			channel = data[6] | (data[7] << 8);
			value = data[8] | (data[9] << 8);
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
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = channel & 0xff;
			buffer[7] = (channel >> 8);

			buffer[8] = value & 0xff;
			buffer[9] = (value >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmRequestRgbwChannelEvent::PwmRequestRgbwChannelEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmRequestRgbwChannelEvent>(data[4] | (data[5] << 8), callback)
		{
			channel = data[6] | (data[7] << 8);
		}

		uint16_t
		PwmRequestRgbwChannelEvent::getChannel() const
		{
			return channel;
		}

		std::unique_ptr< const uint8_t[] >
		PwmRequestRgbwChannelEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = channel & 0xff;
			buffer[7] = (channel >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmRgbwChannelReadyEvent::PwmRgbwChannelReadyEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmRgbwChannelReadyEvent>(data[4] | (data[5] << 8), callback)
		{
			channel = data[6] | (data[7] << 8);
			value.red = data[8] | (data[9] << 8);
			value.green = data[10] | (data[11] << 8);
			value.blue = data[12] | (data[13] << 8);
			value.white = data[14] | (data[15] << 8);
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
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = channel & 0xff;
			buffer[7] = (channel >> 8);

			buffer[8] = value.red & 0xff;
			buffer[9] = (value.red >> 8);

			buffer[10] = value.green & 0xff;
			buffer[11] = (value.green >> 8);

			buffer[12] = value.blue & 0xff;
			buffer[13] = (value.blue >> 8);

			buffer[14] = value.white & 0xff;
			buffer[15] = (value.white >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmUpdateRgbwChannelEvent::PwmUpdateRgbwChannelEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmUpdateRgbwChannelEvent>(data[4] | (data[5] << 8), callback)
		{
			channel = data[6] | (data[7] << 8);
			value.red = data[8] | (data[9] << 8);
			value.green = data[10] | (data[11] << 8);
			value.blue = data[12] | (data[13] << 8);
			value.white = data[14] | (data[15] << 8);
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
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = channel & 0xff;
			buffer[7] = (channel >> 8);

			buffer[8] = value.red & 0xff;
			buffer[9] = (value.red >> 8);

			buffer[10] = value.green & 0xff;
			buffer[11] = (value.green >> 8);

			buffer[12] = value.blue & 0xff;
			buffer[13] = (value.blue >> 8);

			buffer[14] = value.white & 0xff;
			buffer[15] = (value.white >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmUpdateSuccessEvent::PwmUpdateSuccessEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmUpdateSuccessEvent>(data[4] | (data[5] << 8), callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		PwmUpdateSuccessEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		PwmErrorEvent::PwmErrorEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<PwmErrorEvent>(data[4] | (data[5] << 8), callback)
		{
			error = static_cast< PwmError >(data[6]);
		}

		PwmError
		PwmErrorEvent::getError() const
		{
			return error;
		}

		std::unique_ptr< const uint8_t[] >
		PwmErrorEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << EVENT_LENGTH
					<< ").\r\n";

				return std::unique_ptr< const uint8_t[] >();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = static_cast< uint8_t >(error);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}
	}
}
