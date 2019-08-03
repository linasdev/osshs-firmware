/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/events/event_packet.hpp>
#include <prettyhome/events/event_factory.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		EventPacket::EventPacket(std::unique_ptr< const uint8_t[] > data, EventCallback callback)
		{
			multiTarget = (buffer[2] >> 7) & 0b1;
			command = (buffer[2] >> 6) & 0b1;

			transmitterMac = buffer[3] | (buffer[4] << 8) | (buffer[5] << 16) | (buffer[6] << 24);

			std::unique_ptr< const uint8_t[] > serializedEvent;

			if (multiTarget)
			{
				serializedEvent.reset(&buffer[7]);
			}
			else
			{
				transmitterMac = buffer[7] | (buffer[8] << 8) | (buffer[9] << 16) | (buffer[10] << 24);
				serializedEvent.reset(&buffer[11]);
			}

			uint16_t eventType = serializedEvent[2] | (serializedEvent[3] << 8);
			event = events::EventFactory::make(eventType, serializedEvent, events::Event::CAUSE_ID_GENERATE, callback);
		}

		bool
		EventPacket::isMultiTarget() const
		{
			return multiTarget;
		}

		bool
		EventPacket::isCommand() const
		{
			return command;
		}

		uint32_t
		EventPacket::getTransmitterMac() const
		{
			return transmitterMac;
		}

		uint32_t
		EventPacket::getReceiverMac() const
		{
			return receiverMac;
		}

		std::shared_ptr< events::Event >
		EventPacket::getEvent() const
		{
			return event;
		}

		std::unique_ptr< const uint8_t[] >
		EventPacket::serialize() const
		{
			std::unique_ptr< const uint8_t[] > serializedEvent = event->serialize();
			uint16_t eventLength = serializedEvent[0] | (serializedEvent[1] << 8);

			uint16_t packetLength = multiTarget ? (eventLength + 7) : (eventLength + 11);

			uint8_t *buffer = new uint8_t[packetLength];

			buffer[0] = packetLength & 0xff;
			buffer[1] = (packetLength >> 8);

			buffer[2]  = (multiTarget << 7);
			buffer[2] |= (command << 6);
			buffer[2] |= (0b0 << 5);
			buffer[2] |= (0b0 << 4);
			buffer[2] |= (0b0 << 3);
			buffer[2] |= (0b0 << 2);
			buffer[2] |= (0b0 << 1);
			buffer[2] |= (0b0 << 0);

			buffer[3] = transmitterMac & 0xff;
			buffer[4] = (transmitterMac >> 8) & 0xff;
			buffer[5] = (transmitterMac >> 16) & 0xff;
			buffer[6] = (transmitterMac >> 24);

			if (multiTarget)
			{
				for (uint16_t i = 0; i < eventLength; i++)
					buffer[7 + i] = serializedEvent[i];
			}
			else
			{
				buffer[7] = receiverMac & 0xff;
				buffer[8] = (receiverMac >> 8) & 0xff;
				buffer[9] = (receiverMac >> 16) & 0xff;
				buffer[10] = (receiverMac >> 24);

				for (uint16_t i = 0; i < eventLength; i++)
					buffer[11 + i] = serializedEvent[i];
			}

			return std::unique_ptr< const uint8_t[] >(buffer);
		}
	}
}