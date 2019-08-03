/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_MODULE_MANAGER_HPP
#define PRETTYHOME_MODULE_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include <modm/processing/protothread.hpp>
#include <prettyhome/modules/module.hpp>
#include <prettyhome/events/event.hpp>
#include <prettyhome/events/event_selector.hpp>

namespace prettyhome
{
	namespace modules
	{
		class ModuleManager : public modm::pt::Protothread
		{
		public:
			static void
			initialize();

			static void
			registerModule(modules::Module *module);

			static bool
			run();
		private:
			static std::vector< modules::Module* > modules;
		};
	}
}

#endif  // PRETTYHOME_MODULE_MANAGER_HPP