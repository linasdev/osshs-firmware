/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/modules/module_manager.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	namespace modules
	{
		std::vector< modules::Module* > ModuleManager::modules;

		void
		ModuleManager::initialize()
		{
			PRETTYHOME_LOG_INFO("Initializing module manager.");
		}

		void
		ModuleManager::registerModule(modules::Module *module)
		{
			PRETTYHOME_LOG_INFO_STREAM << "Registering module(type = " << module->getModuleTypeId() << ").\r\n";

			modules.push_back(module);
			module->initialize();
		}

		void
		ModuleManager::run()
		{
			for (modules::Module *module : modules)
			{
				module->run();
			}
		}
	}
}
