/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EEPROM_MODULE_HPP
#define PRETTYHOME_EEPROM_MODULE_HPP

#include <modm/driver/storage/i2c_eeprom.hpp>
#include <modm/processing/timer.hpp>
#include <prettyhome/modules/module.hpp>
#include <prettyhome/events/eeprom_event.hpp>

namespace prettyhome
{
	namespace modules
	{
		static constexpr uint8_t EEPROM_MODULE_ID = 0x01;

 		template < typename I2cMaster, uint16_t writeCycleTime = 5 >
		class EepromModule : public Module, private modm::NestedResumable<1>
		{
		public:
			EepromModule(uint8_t address = 0x50)
				: i2cEeprom(address)
			{
			}

			uint8_t
			getModuleTypeId() const;
		protected:
			bool
			run();
		private:
    	modm::ShortTimeout writeCycleTimeout;
			modm::I2cEeprom< I2cMaster > i2cEeprom;

			std::shared_ptr< events::Event > currentEvent;
			std::shared_ptr< uint8_t[] > currentData;
			bool currentSuccess;

			modm::ResumableResult<void>
			handleRequestDataEvent(std::shared_ptr< events::EepromRequestDataEvent > event);

			modm::ResumableResult<void>
			handleUpdateDataEvent(std::shared_ptr< events::EepromUpdateDataEvent > event);
	  };
	}
}

#include <prettyhome/modules/eeprom_module_impl.hpp>

#endif  // PRETTYHOME_EEPROM_MODULE_HPP