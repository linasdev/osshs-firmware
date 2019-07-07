/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_MODULE_HPP
#define PRETTYHOME_MODULE_HPP

#include <cstdint>

#include <prettyhome/event.hpp>

namespace prettyhome
{
	class System;

	namespace modules
	{
		static constexpr uint8_t BASE_MODULE_ID = 0x00;

		class Module
	  {
		public:
			Module();

			virtual uint8_t
			getModuleTypeId() const = 0;
		protected:
			virtual void
			subscribeEvents();

			virtual void
			handleEvent(Event &event) = 0;
		private:
			Module(const Module&) = delete;

			Module&
			operator=(const Module&) = delete;

			friend class prettyhome::System;
	  };
	}
}

#endif  // PRETTYHOME_MODULE_HPP