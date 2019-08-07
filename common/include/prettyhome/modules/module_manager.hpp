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
#include <prettyhome/modules/module.hpp>

namespace prettyhome
{
	namespace modules
	{
		class ModuleManager
		{
		public:
			/**
			 * @brief Initialize the module manager.
			 * 
			 */
			static void
			initialize();

			/**
			 * @brief Register a module.
			 * 
			 * @param module module to register.
			 */
			static void
			registerModule(modules::Module *module);

			/**
			 * @brief Update all registered modules.
			 * 
			 */
			static void
			update();
		private:
			static std::vector< modules::Module* > modules;
		};
	}
}

#endif  // PRETTYHOME_MODULE_MANAGER_HPP
