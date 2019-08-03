/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EVENT_PACKET_HPP
#define PRETTYHOME_EVENT_PACKET_HPP

#include <memory>
#include <prettyhome/events/event.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		class EventPacket
		{
		public:
			static constexpr uint32_t NULL_MAC = static_cast< uint32_t >(-1);

			EventPacket(std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);

			EventPacket(std::shared_ptr< events::Event > event, uint32_t transmitterMac, uint32_t receiverMac = NULL_MAC, bool command = false)
				: multiTarget(receiverMac == NULL_MAC), command(command), transmitterMac(transmitterMac), receiverMac(receiverMac), event(event)
			{
			}

			bool
			isMultiTarget() const;

			bool
			isCommand() const;

			uint32_t
			getTransmitterMac() const;

			uint32_t
			getReceiverMac() const;

			std::shared_ptr< events::Event >
			getEvent() const;

			std::unique_ptr< const uint8_t[] >
			serialize() const;
		private:
			bool multiTarget;
			bool command;
			uint32_t transmitterMac;
			uint32_t receiverMac;
			std::shared_ptr< events::Event > event;
		};
	}
}
#endif  // PRETTYHOME_EVENT_PACKET_HPP