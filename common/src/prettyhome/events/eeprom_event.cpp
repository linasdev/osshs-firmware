/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/events/eeprom_event.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	namespace events
	{
		EepromRequestDataEvent::EepromRequestDataEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
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

		std::unique_ptr< const uint8_t[] >
		EepromRequestDataEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				PRETTYHOME_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
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

			buffer[6] = address & 0xff;
			buffer[7] = (address >> 8);

			buffer[8] = dataLen & 0xff;
			buffer[9] = (dataLen >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		EepromDataReadyEvent::EepromDataReadyEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<EepromDataReadyEvent>(data[4] | (data[5] << 8), callback)
		{
			dataLen = data[6] | (data[7] << 8);

			if (8 + dataLen == (data[0] | (data[1] << 8)))
			{
				for (uint16_t i = 0; i < dataLen; i++)
				{
					this->data[i] = data[8 + i];
				}
			}
			else
			{
			}
		}

		const std::shared_ptr< uint8_t[] >
		EepromDataReadyEvent::getData() const
		{
			return data;
		}

		uint16_t
		EepromDataReadyEvent::getDataLen() const
		{
			return dataLen;
		}

		std::unique_ptr< const uint8_t[] >
		EepromDataReadyEvent::serialize() const
		{
			uint16_t EVENT_LENGTH = 8 + dataLen;
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				PRETTYHOME_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
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

			buffer[6] = dataLen & 0xff;
			buffer[7] = (dataLen >> 8);

			for (uint16_t i = 0; i < dataLen; i++)
			{
				buffer[8 + i] = data[i];
			}

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		EepromUpdateDataEvent::EepromUpdateDataEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<EepromUpdateDataEvent>(data[4] | (data[5] << 8), callback)
		{
			address = data[6] | (data[7] << 8);
			dataLen = data[8] | (data[9] << 8);

			if (10 + dataLen == (data[0] | (data[1] << 8)))
			{
				for (uint16_t i = 0; i < dataLen; i++)
				{
					this->data[i] = data[10 + i];
				}
			}
			else
			{
			}
		}

		uint16_t
		EepromUpdateDataEvent::getAddress() const
		{
			return address;
		}

		const std::shared_ptr< uint8_t[] >
		EepromUpdateDataEvent::getData() const
		{
			return data;
		}

		uint16_t
		EepromUpdateDataEvent::getDataLen() const
		{
			return dataLen;
		}

		std::unique_ptr< const uint8_t[] >
		EepromUpdateDataEvent::serialize() const
		{
			uint16_t EVENT_LENGTH = 8 + dataLen;
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				PRETTYHOME_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
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

			buffer[6] = address & 0xff;
			buffer[7] = (address >> 8);

			buffer[8] = dataLen & 0xff;
			buffer[9] = (dataLen >> 8);

			for (uint16_t i = 0; i < dataLen; i++)
			{
				buffer[10 + i] = data[i];
			}

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		EepromUpdateSuccessEvent::EepromUpdateSuccessEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<EepromUpdateSuccessEvent>(data[4] | (data[5] << 8), callback)
		{
			static_cast< void >(data);
		}

		std::unique_ptr< const uint8_t[] >
		EepromUpdateSuccessEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				PRETTYHOME_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
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


		EepromErrorEvent::EepromErrorEvent(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
			: EventRegistrar<EepromErrorEvent>(data[4] | (data[5] << 8), callback)
		{
			error = static_cast< EepromError >(data[6]);
		}

		EepromError
		EepromErrorEvent::getError() const
		{
			return error;
		}

		std::unique_ptr< const uint8_t[] >
		EepromErrorEvent::serialize() const
		{
			uint8_t *buffer = new (std::nothrow) uint8_t[EVENT_LENGTH];

			if (buffer == nullptr)
			{
				PRETTYHOME_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
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
