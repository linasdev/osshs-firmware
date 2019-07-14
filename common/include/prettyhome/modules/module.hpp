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
#include <queue>

#include <modm/processing/protothread.hpp>
#include <modm/processing/resumable.hpp>
#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	class System;

	namespace modules
	{
		static constexpr uint8_t BASE_MODULE_ID = 0x00;

		class Module : public modm::pt::Protothread
		{
		public:
			Module();

			virtual uint8_t
			getModuleTypeId() const = 0;
		protected:
			std::queue< std::shared_ptr< events::Event > > eventQueue;

			virtual void
			subscribeEvents();

			virtual bool
			run() = 0;

			void
			handleEvent(std::shared_ptr< events::Event > event);
		private:
			Module(const Module&) = delete;

			Module&
			operator=(const Module&) = delete;

			friend class prettyhome::System;
		};
	}
}

#endif  // PRETTYHOME_MODULE_HPP