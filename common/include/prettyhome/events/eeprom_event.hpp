/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EEPROM_EVENT_HPP
#define PRETTYHOME_EEPROM_EVENT_HPP

#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace events
	{
		enum class EepromEvent
		{
			BASE = 0x01 << 8,

			REQUEST_DATA,
			DATA_READY,

			UPDATE_DATA,
			UPDATE_SUCCESS,

			ERROR
		};

		enum class EepromError : uint8_t
		{
			READ_FAILED,
			WRITE_FAILED
		};

		class EepromRequestDataEvent : public Event
		{
		public:
			EepromRequestDataEvent(uint16_t address, size_t dataLen, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::REQUEST_DATA), callback), address(address), dataLen(dataLen)
			{
			}

			EepromRequestDataEvent(uint16_t address, size_t dataLen, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::REQUEST_DATA), causeId, callback), address(address), dataLen(dataLen)
			{
			}

			uint16_t
			getAddress() const;

			size_t
			getDataLen() const;
		private:
			uint16_t address;
			size_t dataLen;
		};

		class EepromDataReadyEvent : public Event
		{
		public:
			EepromDataReadyEvent(const std::shared_ptr< uint8_t[] > data, size_t dataLen, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::DATA_READY), callback), data(data), dataLen(dataLen)
			{
			}

			EepromDataReadyEvent(const std::shared_ptr< uint8_t[] > data, size_t dataLen, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::DATA_READY), causeId, callback), data(data), dataLen(dataLen)
			{
			}

			const std::shared_ptr< uint8_t[] >
			getData() const;

			size_t
			getDataLen() const;
		private:
			const std::shared_ptr< uint8_t[] > data;
			size_t dataLen;
		};

		class EepromUpdateDataEvent : public Event
		{
		public:
			EepromUpdateDataEvent(uint16_t address, const std::shared_ptr< uint8_t[] > data, size_t dataLen, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::UPDATE_DATA), callback), address(address), data(data), dataLen(dataLen)
			{
			}

			EepromUpdateDataEvent(uint16_t address, const std::shared_ptr< uint8_t[] > data, size_t dataLen, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::UPDATE_DATA), causeId, callback), address(address), data(data), dataLen(dataLen)
			{
			}

			uint16_t
			getAddress() const;

			const std::shared_ptr< uint8_t[] >
			getData() const;

			size_t
			getDataLen() const;
		private:
			uint16_t address;
			const std::shared_ptr< uint8_t[] > data;
			size_t dataLen;
		};

		class EepromUpdateSuccessEvent : public Event
		{
		public:
			EepromUpdateSuccessEvent(EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::UPDATE_SUCCESS), callback)
			{
			}

			EepromUpdateSuccessEvent(uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::UPDATE_SUCCESS), causeId, callback)
			{
			}
		};

		class EepromErrorEvent : public Event
		{
		public:
			EepromErrorEvent(EepromError error, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::ERROR), callback), error(error)
			{
			}

			EepromErrorEvent(EepromError error, uint16_t causeId, EventCallback callback = nullptr)
				: Event(static_cast< uint16_t > (EepromEvent::ERROR), causeId, callback), error(error)
			{
			}

			EepromError
			getError() const;
		private:
			EepromError error;
		};
	}
}
#endif  // PRETTYHOME_EEPROM_EVENT_HPP