/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/modules/eeprom_module.hpp>
#include <prettyhome/log/logger.hpp>
namespace prettyhome
{
	namespace modules
	{
		EepromModule::EepromModule()
		{

		}

		uint8_t
		EepromModule::getModuleTypeId() const
		{
			return EEPROM_MODULE_ID;
		}

		void
		EepromModule::handleEvent(Event &event)
		{
			PRETTYHOME_LOG_ERROR << event.getType() << "\r\n";
		}
	}
}