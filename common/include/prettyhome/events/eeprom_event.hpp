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
#include <prettyhome/modules/eeprom_module.hpp>

namespace prettyhome
{
	namespace events
	{
		enum class EepromEvent
		{
			REQUEST_DATA_EVENT = modules::EEPROM_MODULE_ID << 8,
			DATA_READY_EVENT,
			UPDATE_DATA_EVENT,
			UPDATE_SUCCESS_EVENT,
			ERROR_EVENT
		};

		class EepromRequestDataEvent : public Event
		{
		public:
			EepromRequestDataEvent(uint16_t address, size_t dataLen, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::REQUEST_DATA_EVENT, callback, formChannel), address(address), dataLen(dataLen)
			{
			}

			EepromRequestDataEvent(uint16_t address, size_t dataLen, uint16_t causeId, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::REQUEST_DATA_EVENT, causeId, callback, formChannel), address(address), dataLen(dataLen)
			{
			}

			uint8_t
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
			EepromDataReadyEvent(const uint8_t *data, size_t dataLen, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::DATA_READY_EVENT, callback, formChannel), data(data), dataLen(dataLen)
			{
			}

			EepromDataReadyEvent(const uint8_t *data, size_t dataLen, uint16_t causeId, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::DATA_READY_EVENT, causeId, callback, formChannel), data(data), dataLen(dataLen)
			{
			}

			const uint8_t *
			getData() const;

			size_t
			getDataLen() const;
		private:
			const uint8_t *data;
			size_t dataLen;
		};

		class EepromUpdateDataEvent : public Event
		{
		public:
			EepromUpdateDataEvent(uint16_t address, const uint8_t *data, size_t dataLen, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::UPDATE_DATA_EVENT, callback, formChannel), address(address), data(data), dataLen(dataLen)
			{
			}

			EepromUpdateDataEvent(uint16_t address, const uint8_t *data, size_t dataLen, uint16_t causeId, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::UPDATE_DATA_EVENT, causeId, callback, formChannel), address(address), data(data), dataLen(dataLen)
			{
			}

			uint16_t
			getAddress() const;

			const uint8_t *
			getData() const;

			size_t
			getDataLen() const;
		private:
			uint16_t address;
			const uint8_t *data;
			size_t dataLen;
		};

		class EepromUpdateSuccessEvent : public Event
		{
		public:
			EepromUpdateSuccessEvent(EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::UPDATE_SUCCESS_EVENT, callback, formChannel)
			{
			}

			EepromUpdateSuccessEvent(uint16_t causeId, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::UPDATE_SUCCESS_EVENT, causeId, callback, formChannel)
			{
			}
		};

		class EepromErrorEvent : public Event
		{
			EepromErrorEvent(uint8_t errorCode, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::ERROR_EVENT, callback, formChannel), errorCode(errorCode)
			{
			}

			EepromErrorEvent(uint8_t errorCode, uint16_t causeId, EventCallback callback = nullptr, bool formChannel = false)
				: Event((uint16_t) EepromEvent::ERROR_EVENT, causeId, callback, formChannel), errorCode(errorCode)
			{
			}

			uint8_t
			getErrorCode() const;
		private:
			uint8_t errorCode;
		};
	}
}
#endif  // PRETTYHOME_EEPROM_EVENT_HPP