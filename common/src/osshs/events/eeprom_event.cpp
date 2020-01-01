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

#include <osshs/events/eeprom_event.hpp>
#include <osshs/log/logger.hpp>

namespace osshs
{
	namespace events
	{
		EepromRequestDataEvent::EepromRequestDataEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback)
			: EventRegistrar<EepromRequestDataEvent>(data[4] | (data[5] << 8), callback)
		{
			address = data[6] | (data[7] << 8);
			dataLen = data[8] | (data[9] << 8);
		}

		uint16_t
		EepromRequestDataEvent::getAddress() const
		{
			return address;
		}

		uint16_t
		EepromRequestDataEvent::getDataLen() const
		{
			return dataLen;
		}

		std::unique_ptr<const uint8_t[]>
		EepromRequestDataEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR("Failed to allocate memory for a buffer(bufferLength = %u).", EVENT_LENGTH);
				return std::unique_ptr<const uint8_t[]>();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = address & 0xff;
			buffer[7] = (address >> 8);

			buffer[8] = dataLen & 0xff;
			buffer[9] = (dataLen >> 8);

			return std::unique_ptr<const uint8_t[]>(buffer);
		}


		EepromDataReadyEvent::EepromDataReadyEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback)
			: EventRegistrar<EepromDataReadyEvent>(data[4] | (data[5] << 8), callback)
		{
			uint16_t eventLength = data[0] | (data[1] << 8);
			dataLen = data[6] | (data[7] << 8);

			if (8 + dataLen != eventLength)
			{
				OSSHS_LOG_WARNING("Failed to construct an epprom data ready event(eventLength = %u, dataLength = %u).", eventLength, dataLen);
				return;
			}

			this->data.reset(new (std::nothrow) uint8_t[dataLen]);

			if (this->data == nullptr)
			{
				OSSHS_LOG_ERROR("Failed to allocate memory for a buffer(bufferLength = %u).", dataLen);
				return;
			}

			std::copy(&data[8], &data[8 + dataLen], &this->data[0]);
		}

		const std::shared_ptr<uint8_t[]>
		EepromDataReadyEvent::getData() const
		{
			return data;
		}

		uint16_t
		EepromDataReadyEvent::getDataLen() const
		{
			return dataLen;
		}

		std::unique_ptr<const uint8_t[]>
		EepromDataReadyEvent::serialize() const
		{
			uint16_t EVENT_LENGTH = 8 + dataLen;
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR("Failed to allocate memory for a buffer(bufferLength = %u).", EVENT_LENGTH);
				return std::unique_ptr<const uint8_t[]>();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = dataLen & 0xff;
			buffer[7] = (dataLen >> 8);

			std::copy(&data[0], &data[dataLen], &buffer[8]);

			return std::unique_ptr<const uint8_t[]>(buffer);
		}


		EepromUpdateDataEvent::EepromUpdateDataEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback)
			: EventRegistrar<EepromUpdateDataEvent>(data[4] | (data[5] << 8), callback)
		{
			uint16_t eventLength = data[0] | (data[1] << 8);
			address = data[6] | (data[7] << 8);
			dataLen = data[8] | (data[9] << 8);

			if (10 + dataLen != eventLength)
			{
				OSSHS_LOG_WARNING("Failed to construct an epprom update data event(eventLength = %u, dataLength = %u).", eventLength, dataLen);
				return;
			}

			this->data.reset(new (std::nothrow) uint8_t[dataLen]);

			if (this->data == nullptr)
			{
				OSSHS_LOG_ERROR("Failed to allocate memory for a buffer(bufferLength = %u).", dataLen);
				return;
			}

			std::copy(&data[10], &data[10 + dataLen], &this->data[0]);
		}

		uint16_t
		EepromUpdateDataEvent::getAddress() const
		{
			return address;
		}

		const std::shared_ptr<uint8_t[]>
		EepromUpdateDataEvent::getData() const
		{
			return data;
		}

		uint16_t
		EepromUpdateDataEvent::getDataLen() const
		{
			return dataLen;
		}

		std::unique_ptr<const uint8_t[]>
		EepromUpdateDataEvent::serialize() const
		{
			uint16_t EVENT_LENGTH = 8 + dataLen;
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR("Failed to allocate memory for a buffer(bufferLength = %u).", EVENT_LENGTH);
				return std::unique_ptr<const uint8_t[]>();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = address & 0xff;
			buffer[7] = (address >> 8);

			buffer[8] = dataLen & 0xff;
			buffer[9] = (dataLen >> 8);

			std::copy(&data[0], &data[dataLen], &buffer[10]);

			return std::unique_ptr<const uint8_t[]>(buffer);
		}


		EepromUpdateSuccessEvent::EepromUpdateSuccessEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback)
			: EventRegistrar<EepromUpdateSuccessEvent>(data[4] | (data[5] << 8), callback)
		{
			static_cast<void>(data);
		}

		std::unique_ptr<const uint8_t[]>
		EepromUpdateSuccessEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR("Failed to allocate memory for a buffer(bufferLength = %u).", EVENT_LENGTH);
				return std::unique_ptr<const uint8_t[]>();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			return std::unique_ptr<const uint8_t[]>(buffer);
		}


		EepromErrorEvent::EepromErrorEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback)
			: EventRegistrar<EepromErrorEvent>(data[4] | (data[5] << 8), callback)
		{
			error = static_cast<EepromError>(data[6]);
		}

		EepromError
		EepromErrorEvent::getError() const
		{
			return error;
		}

		std::unique_ptr<const uint8_t[]>
		EepromErrorEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				OSSHS_LOG_ERROR("Failed to allocate memory for a buffer(bufferLength = %u).", EVENT_LENGTH);
				return std::unique_ptr<const uint8_t[]>();
			}

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = causeId & 0xff;
			buffer[5] = (causeId >> 8);

			buffer[6] = static_cast<uint8_t>(error);

			return std::unique_ptr<const uint8_t[]>(buffer);
		}
	}
}
