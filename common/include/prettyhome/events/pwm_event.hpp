/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_PWM_EVENT_HPP
#define PRETTYHOME_PWM_EVENT_HPP

#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace events
	{
		enum class PwmEvent : uint16_t
		{
			BASE = 0x02 << 8,

			REQUEST_STATUS,
			STATUS_READY,

			ENABLE,
			DISABLE,

			REQUEST_CHANNEL,
			CHANNEL_READY,

			UPDATE_CHANNEL,

			REQUEST_RGBW_CHANNEL,
			RGBW_CHANNEL_READY,

			UPDATE_RGBW_CHANNEL,

			UPDATE_SUCCESS,
			ERROR
		};

		enum class PwmStatus : uint8_t
		{
			ENABLED,
			DISABLED
		};

		enum class PwmError : uint8_t
		{
			CHANNEL_OUT_OF_BOUNDS,
			VALUE_OUT_OF_BOUNDS
		};

		typedef struct PwmRgbwValue
		{
			uint16_t red;
			uint16_t green;
			uint16_t blue;
			uint16_t white;

			PwmRgbwValue(uint16_t red, uint16_t green, uint16_t blue, uint16_t white)
			{
				this->red = red;
				this->green = green;
				this->blue = blue;
				this->white = white;
			}
		} PwmRgbwValue;

		class PwmRequestStatusEvent : public Event
		{
		public:
			PwmRequestStatusEvent(EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::REQUEST_STATUS), callback)
			{
			}

			PwmRequestStatusEvent(uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::REQUEST_STATUS), causeId, callback)
			{
			}
		};

		class PwmStatusReadyEvent : public Event
		{
		public:

			PwmStatusReadyEvent(uint8_t status, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::STATUS_READY), callback), status(status)
			{
			}

			PwmStatusReadyEvent(uint8_t status, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::STATUS_READY), causeId, callback), status(status)
			{
			}

			uint8_t
			getStatus() const;
		private:
			uint8_t status;
		};

		class PwmEnableEvent : public Event
		{
		public:
			PwmEnableEvent(EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::ENABLE), callback)
			{
			}

			PwmEnableEvent(uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::ENABLE), causeId, callback)
			{
			}
		};

		class PwmDisableEvent : public Event
		{
		public:
			PwmDisableEvent(EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::DISABLE), callback)
			{
			}

			PwmDisableEvent(uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::DISABLE), causeId, callback)
			{
			}
		};

		class PwmRequestChannelEvent : public Event
		{
		public:
			PwmRequestChannelEvent(uint16_t channel, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::REQUEST_CHANNEL), callback), channel(channel)
			{
			}

			PwmRequestChannelEvent(uint16_t channel, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::REQUEST_CHANNEL), causeId, callback), channel(channel)
			{
			}

			uint16_t
			getChannel() const;
		private:
			uint16_t channel;
		};

		class PwmChannelReadyEvent : public Event
		{
		public:
			PwmChannelReadyEvent(uint16_t channel, uint16_t value, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::CHANNEL_READY), callback), channel(channel), value(value)
			{
			}

			PwmChannelReadyEvent(uint16_t channel, uint16_t value, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::CHANNEL_READY), causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			uint16_t
			getValue() const;
		private:
			uint16_t channel;
			uint16_t value;
		};

		class PwmUpdateChannelEvent : public Event
		{
		public:
			PwmUpdateChannelEvent(uint16_t channel, uint16_t value, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::UPDATE_CHANNEL), callback), channel(channel), value(value)
			{
			}

			PwmUpdateChannelEvent(uint16_t channel, uint16_t value, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::UPDATE_CHANNEL), causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			uint16_t
			getValue() const;
		private:
			uint16_t channel;
			uint16_t value;
		};

		class PwmRequestRgbwChannelEvent : public Event
		{
		public:
			PwmRequestRgbwChannelEvent(uint16_t channel, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::REQUEST_RGBW_CHANNEL), callback), channel(channel)
			{
			}

			PwmRequestRgbwChannelEvent(uint16_t channel, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::REQUEST_RGBW_CHANNEL), causeId, callback), channel(channel)
			{
			}

			uint16_t
			getChannel() const;
		private:
			uint16_t channel;
		};

		class PwmRgbwChannelReadyEvent : public Event
		{
		public:
			PwmRgbwChannelReadyEvent(uint16_t channel, PwmRgbwValue value, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::RGBW_CHANNEL_READY), callback), channel(channel), value(value)
			{
			}

			PwmRgbwChannelReadyEvent(uint16_t channel, PwmRgbwValue value, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::RGBW_CHANNEL_READY), causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			PwmRgbwValue
			getValue() const;
		private:
			uint16_t channel;
			PwmRgbwValue value;
		};

		class PwmUpdateRgbwChannelEvent : public Event
		{
		public:
			PwmUpdateRgbwChannelEvent(uint16_t channel, PwmRgbwValue value, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::UPDATE_RGBW_CHANNEL), callback), channel(channel), value(value)
			{
			}

			PwmUpdateRgbwChannelEvent(uint16_t channel, PwmRgbwValue value, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::UPDATE_RGBW_CHANNEL), causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			PwmRgbwValue
			getValue() const;
		private:
			uint16_t channel;
			PwmRgbwValue value;
		};

		class PwmUpdateSuccessEvent : public Event
		{
		public:
			PwmUpdateSuccessEvent(EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::UPDATE_SUCCESS), callback)
			{
			}

			PwmUpdateSuccessEvent(uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::UPDATE_SUCCESS), causeId, callback)
			{
			}
		};

		class PwmErrorEvent : public Event
		{
		public:
			PwmErrorEvent(PwmError error, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::ERROR), callback), error(error)
			{
			}

			PwmErrorEvent(PwmError error, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (PwmEvent::ERROR), causeId, callback), error(error)
			{
			}

			PwmError
			getError() const;
		private:
			PwmError error;
		};
	}
}
#endif  // PRETTYHOME_PWM_EVENT_HPP