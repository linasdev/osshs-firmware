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

#include <prettyhome/modules/module.hpp>

namespace prettyhome
{
	namespace modules
	{
		static constexpr uint8_t EEPROM_MODULE_ID = 0x01;

		class EepromModule : public Module
		{
		public:
			EepromModule();

			uint8_t
			getModuleTypeId() const;
		protected:
			void
			handleEvent(std::shared_ptr< events::Event > event);
	  };
	}
}

#endif  // PRETTYHOME_EEPROM_MODULE_HPP