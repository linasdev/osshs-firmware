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

#ifndef OSSHS_EEPROM_EVENT_HPP
#define OSSHS_EEPROM_EVENT_HPP

#include <osshs/events/event_registrar.hpp>

namespace osshs
{
	namespace events
	{
		enum class EepromEvent : uint16_t
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

		class EepromRequestDataEvent : public EventRegistrar<EepromRequestDataEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 10;
			static constexpr uint16_t TYPE = static_cast< uint16_t > (EepromEvent::REQUEST_DATA);

			EepromRequestDataEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);

			EepromRequestDataEvent(uint16_t address, uint16_t dataLen, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<EepromRequestDataEvent>(causeId, callback), address(address), dataLen(dataLen)
			{
			}

			uint16_t
			getAddress() const;

			uint16_t
			getDataLen() const;

			std::unique_ptr< const uint8_t[] >
			serialize() const;
		private:
			uint16_t address;
			uint16_t dataLen;
		};

		class EepromDataReadyEvent : public EventRegistrar<EepromDataReadyEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 0;
			static constexpr uint16_t TYPE = static_cast< uint16_t > (EepromEvent::DATA_READY);

			EepromDataReadyEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);

			EepromDataReadyEvent(const std::shared_ptr< uint8_t[] > data, uint16_t dataLen, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<EepromDataReadyEvent>(causeId, callback), data(data), dataLen(dataLen)
			{
			}

			const std::shared_ptr< uint8_t[] >
			getData() const;

			uint16_t
			getDataLen() const;

			std::unique_ptr< const uint8_t[] >
			serialize() const;
		private:
			std::shared_ptr< uint8_t[] > data;
			uint16_t dataLen;
		};

		class EepromUpdateDataEvent : public EventRegistrar<EepromUpdateDataEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 0;
			static constexpr uint16_t TYPE = static_cast< uint16_t > (EepromEvent::UPDATE_DATA);

			EepromUpdateDataEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);

			EepromUpdateDataEvent(uint16_t address, const std::shared_ptr< uint8_t[] > data, uint16_t dataLen, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<EepromUpdateDataEvent>(causeId, callback), address(address), data(data), dataLen(dataLen)
			{
			}

			uint16_t
			getAddress() const;

			const std::shared_ptr< uint8_t[] >
			getData() const;

			uint16_t
			getDataLen() const;

			std::unique_ptr< const uint8_t[] >
			serialize() const;
		private:
			uint16_t address;
			std::shared_ptr< uint8_t[] > data;
			uint16_t dataLen;
		};

		class EepromUpdateSuccessEvent : public EventRegistrar<EepromUpdateSuccessEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 6;
			static constexpr uint16_t TYPE = static_cast< uint16_t > (EepromEvent::UPDATE_SUCCESS);

			EepromUpdateSuccessEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);

			EepromUpdateSuccessEvent(uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<EepromUpdateSuccessEvent>(causeId, callback)
			{
			}

			std::unique_ptr< const uint8_t[] >
			serialize() const;
		};

		class EepromErrorEvent : public EventRegistrar<EepromErrorEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 7;
			static constexpr uint16_t TYPE = static_cast< uint16_t > (EepromEvent::ERROR);

			EepromErrorEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);

			EepromErrorEvent(EepromError error, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<EepromErrorEvent>(causeId, callback), error(error)
			{
			}

			EepromError
			getError() const;

			std::unique_ptr< const uint8_t[] >
			serialize() const;
		private:
			EepromError error;
		};
	}
}
#endif  // OSSHS_EEPROM_EVENT_HPP
