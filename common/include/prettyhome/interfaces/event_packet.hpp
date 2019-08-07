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

			/**
			 * @brief Construct event packet from serialized data.
			 * 
			 * @param data serialized event packet.
			 * @param callback callback for underlying event.
			 */
			EventPacket(std::unique_ptr< const uint8_t[] > data, events::EventCallback callback = nullptr);

			/**
			 * @brief Construct event packet.
			 * 
			 * @param event underlying event.
			 * @param transmitterMac transmitter mac.
			 * @param receiverMac receiver mac or NULL_MAC if event packet is multi target.
			 * @param command whether or not this event packet is a command.
			 */
			EventPacket(std::shared_ptr< events::Event > event, uint32_t transmitterMac, uint32_t receiverMac = NULL_MAC, bool command = false)
				: multiTarget(receiverMac == NULL_MAC), command(command), transmitterMac(transmitterMac), receiverMac(receiverMac), event(event)
			{
			}

			/**
			 * @brief Multi target getter.
			 * 
			 * @return true event packet is multi target.
			 * @return false event packet is not multi target.
			 */
			bool
			isMultiTarget() const;

			/**
			 * @brief Command getter.
			 * 
			 * @return true event packet is a command.
			 * @return false event packet is not a command.
			 */
			bool
			isCommand() const;

			/**
			 * @brief Transmitter mac getter.
			 * 
			 * @return uint32_t transmitter mac.
			 */
			uint32_t
			getTransmitterMac() const;

			/**
			 * @brief Receiver mac getter.
			 * 
			 * @return uint32_t receiver mac.
			 */
			uint32_t
			getReceiverMac() const;

			/**
			 * @brief Event getter.
			 * 
			 * @return std::shared_ptr< events::Event > event contained in this event packet.
			 */
			std::shared_ptr< events::Event >
			getEvent() const;

			/**
			 * @brief Check whether this event packet is malformed.
			 * 
			 * @return true this event packet is malformed.
			 * @return false this event packet is not malformed.
			 */
			bool
			isMalformed() const;

			/**
			 * @brief Serialize this event packet.
			 * 
			 * @return std::unique_ptr< const uint8_t[] > serialized event packet or nullptr if serialization failed.
			 */
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
