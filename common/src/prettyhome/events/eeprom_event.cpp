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
		uint8_t
		EepromRequestDataEvent::getAddress() const
		{
			return address;
		}

		size_t
		EepromRequestDataEvent::getDataLen() const
		{
			return dataLen;
		}


		const uint8_t *
		EepromDataReadyEvent::getData() const
		{
			return data;
		}

		size_t
		EepromDataReadyEvent::getDataLen() const
		{
			return dataLen;
		}


		uint16_t
		EepromUpdateDataEvent::getAddress() const
		{
			return address;
		}

		const uint8_t *
		EepromUpdateDataEvent::getData() const
		{
			return data;
		}

		size_t
		EepromUpdateDataEvent::getDataLen() const
		{
			return dataLen;
		}


		uint8_t
		EepromErrorEvent::getErrorCode() const
		{
			return errorCode;
		}
	}
}