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
			static void
			initialize();

			static void
			registerModule(modules::Module *module);

			static void
			run();
		private:
			static std::vector< modules::Module* > modules;
		};
	}
}

#endif  // PRETTYHOME_MODULE_MANAGER_HPP