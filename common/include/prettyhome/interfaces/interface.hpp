/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_INTERFACE_HPP
#define PRETTYHOME_INTERFACE_HPP

#include <cstdint>
#include <queue>
#include <modm/processing/protothread.hpp>
#include <modm/processing/resumable.hpp>
#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		static constexpr uint8_t BASE_INTERFACE_ID = 0x00;

		class Interface : public modm::pt::Protothread
		{
		public:
			Interface() = default;

			virtual uint8_t
			getInterfaceTypeId() const = 0;
		protected:
			std::queue< std::shared_ptr< events::Event > > eventQueue;

			virtual bool
			run() = 0;

			void
			reportEvent(std::shared_ptr< events::Event > event);
		private:
			Interface(const Interface&) = delete;

			Interface&
			operator=(const Interface&) = delete;

			virtual void
			initialize() = 0;
		};
	}
}

#endif  // PRETTYHOME_INTERFACE_HPP
