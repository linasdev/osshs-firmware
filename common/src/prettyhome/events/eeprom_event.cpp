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

namespace prettyhome
{
	namespace events
	{
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
			constexpr uint16_t EVENT_LENGTH = 8;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = address & 0xff;
			buffer[5] = (address >> 8);

			buffer[6] = dataLen & 0xff;
			buffer[7] = (dataLen >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
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
			uint16_t EVENT_LENGTH = 6 + dataLen;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = dataLen & 0xff;
			buffer[5] = (dataLen >> 8);

			for (uint16_t i = 0; i < dataLen; i++)
			{
				buffer[6 + 1] = data[i];
			}

			return std::unique_ptr< const uint8_t[] >(buffer);
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
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			buffer[4] = address & 0xff;
			buffer[5] = (address >> 8);

			buffer[6] = dataLen & 0xff;
			buffer[7] = (dataLen >> 8);

			for (uint16_t i = 0; i < dataLen; i++)
			{
				buffer[8 + 1] = data[i];
			}

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		std::unique_ptr< const uint8_t[] >
		EepromUpdateSuccessEvent::serialize() const
		{
			constexpr uint16_t EVENT_LENGTH = 4;
			uint8_t *buffer = new uint8_t[EVENT_LENGTH];

			buffer[0] = EVENT_LENGTH & 0xff;
			buffer[1] = (EVENT_LENGTH >> 8);

			buffer[2] = TYPE & 0xff;
			buffer[3] = (TYPE >> 8);

			return std::unique_ptr< const uint8_t[] >(buffer);
		}


		EepromError
		EepromErrorEvent::getError() const
		{
			return error;
		}

		std::unique_ptr< const uint8_t[] >
		EepromErrorEvent::serialize() const
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