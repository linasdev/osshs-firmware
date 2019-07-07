/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/modules/module.hpp>
#include <prettyhome/system.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	namespace modules
	{
		Module::Module()
		{
		}

		void
		Module::subscribeEvents()
		{
			System::subscribeEvent(EventSelector(0xff00, static_cast< uint16_t >(getModuleTypeId()) << 8),
				[=](Event &event) -> void
				{
					this->handleEvent(event);
				}
			);
		}
	}
}