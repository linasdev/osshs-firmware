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

#ifndef OSSHS_EEPROM_MODULE_HPP
#define OSSHS_EEPROM_MODULE_HPP

#include <modm/driver/storage/i2c_eeprom.hpp>
#include <modm/processing/timer.hpp>
#include <osshs/modules/module.hpp>
#include <osshs/events/eeprom_event.hpp>

namespace osshs
{
	namespace modules
	{
 		template <typename I2cMaster, uint16_t writeCycleTime = 5>
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
			modm::I2cEeprom<I2cMaster> i2cEeprom;

			std::shared_ptr<events::Event> currentEvent;
			std::shared_ptr<uint8_t[]> currentData;
			bool currentSuccess;

			modm::ResumableResult<void>
			handleRequestDataEvent(std::shared_ptr<events::EepromRequestDataEvent> event);

			modm::ResumableResult<void>
			handleUpdateDataEvent(std::shared_ptr<events::EepromUpdateDataEvent> event);
	  };
	}
}

#include <osshs/modules/eeprom_module_impl.hpp>

#endif  // OSSHS_EEPROM_MODULE_HPP
