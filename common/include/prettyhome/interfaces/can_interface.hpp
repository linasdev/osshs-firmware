/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_CAN_INTERFACE_HPP
#define PRETTYHOME_CAN_INTERFACE_HPP

#include <prettyhome/interfaces/interface.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		template< typename Can >
		class CanInterface : public Interface, private modm::NestedResumable<1>
		{
		public:
			CanInterface() = default;
		protected:
			bool
			run();
		private:
			std::shared_ptr< events::EventPacket > currentEventPacket;
			std::unique_ptr< const uint8_t[] > currentBuffer;
			uint16_t currentBufferLength;
			uint16_t currentFrameCount;
			uint16_t currentFrameId;

			void
			initialize();

			uint32_t
			generateCurrentFrameIdentifier();

			modm::ResumableResult< void >
			readEventPacket();

			modm::ResumableResult< void >
			writeEventPacket(std::shared_ptr< events::EventPacket > eventPacket);
	  };
	}
}

#include <prettyhome/interfaces/can_interface_impl.hpp>

#endif  // PRETTYHOME_CAN_INTERFACE_HPP