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
  #error	"Don't include this file directly, use 'can_interface.hpp' instead!"
#endif

#include <modm/platform.hpp>
#include <prettyhome/resource_lock.hpp>
#include <prettyhome/events/event_factory.hpp>
#include <prettyhome/interfaces/interface_manager.hpp>

namespace prettyhome
{
	namespace interfaces
	{
			template< typename Can >
			bool
			CanInterface< Can >::run()
			{
				PT_BEGIN();

				do
				{
					PT_WAIT_UNTIL(Can::isMessageAvailable() | !eventPacketQueue.empty());

					if (Can::isMessageAvailable())
					{
						PT_CALL(readEventPacket());
					}
					else
					{
						currentEventPacket = eventPacketQueue.front();
						eventPacketQueue.pop();

						PT_CALL(writeEventPacket(currentEventPacket));

						currentEventPacket.reset();
					}
				}
				while (true);

				PT_END();
			}

			template< typename Can >
			void
			CanInterface< Can >::initialize()
			{
				modm::platform::CanFilter::setFilter(
					0,
					modm::platform::CanFilter::FIFO0,
					modm::platform::CanFilter::ExtendedIdentifier(0),
					modm::platform::CanFilter::ExtendedFilterMask(0)
				);
			}

			template< typename Can >
			uint32_t
			CanInterface< Can >::generateCurrentFrameIdentifier()
			{
				constexpr uint32_t temp_mac = 0x01234567;
				uint32_t identifier = temp_mac & 0xffff;

				identifier |= (0b1 << 28);
				identifier |= currentFrameId ? (0b0 << 27) : (0b1 << 27);
				identifier |= (currentFrameCount > 1) ? (0b1 << 26) : (0b0 << 26);
				identifier |= (0b0 << 25);
				identifier |= (0b0 << 24);
				identifier |= (0b0 << 23);
				identifier |= (0b0 << 22);
				identifier |= (0b0 << 21);
				identifier |= (0b0 << 20);

				identifier |= (((currentFrameId ? currentFrameId : currentFrameCount) & 0xf00) << 8);

				return identifier;
		}

		template< typename Can >
		modm::ResumableResult< void >
		CanInterface< Can >::readEventPacket()
		{
			RF_BEGIN();

			RF_WAIT_UNTIL(ResourceLock< Can >::tryLock());

			{
				modm::can::Message frame;
				if (Can::getMessage(frame))
				{
					if (frame.getIdentifier() & (0b1 << 26))
					{
						uint16_t frameCount = (frame.getIdentifier() >> 8) & 0xf00;
						frameCount |= frame.data[0];

						uint16_t bufferLength = frame.data[1] | (frame.data[2] << 8);
						uint8_t *buffer = new uint8_t[bufferLength];

						for (uint16_t frameId = 0; frameId < frameCount; frameId++)
						{
							if (frameId)
							{
								while (!Can::isMessageAvailable());
								Can::getMessage(frame);
							}

							for (uint16_t i = 1; i < 8; i++)
								buffer[frameId * 7 + i - 1] = frame.data[i];
						}

						std::shared_ptr< EventPacket > eventPacket(new EventPacket(std::unique_ptr< const uint8_t[] >(buffer)));
						InterfaceManager::reportEventPacket(eventPacket);
					}
					else
					{
						uint16_t bufferLength = frame.data[0] | (frame.data[1] << 8);
						uint8_t *buffer = new uint8_t[bufferLength];

						for (uint16_t i = 0; i < bufferLength; i++)
							buffer[i] = frame.data[i];

						std::shared_ptr< EventPacket > eventPacket(new EventPacket(std::unique_ptr< const uint8_t[] >(buffer)));
						InterfaceManager::reportEventPacket(eventPacket);
					}
				}
				else
				{
				}
			}

			ResourceLock< Can >::unlock();

			RF_END();
		}

		template< typename Can >
		modm::ResumableResult< void >
		CanInterface< Can >::writeEventPacket(std::shared_ptr< EventPacket > eventPacket)
		{
			RF_BEGIN();

			currentBuffer = eventPacket->serialize();
			currentBufferLength = currentBuffer[0] | (currentBuffer[1] << 8);
			if (!((currentBufferLength - 1) / 8))
			{
				currentFrameCount = 1;
			}
			else
			{
				currentFrameCount = 1 + ((currentBufferLength - 1) / 7);
			}
			currentFrameId = 0;

			if (currentFrameCount == 1)
			{
				modm::can::Message frame(generateCurrentFrameIdentifier(), currentBufferLength);
				frame.setExtended(true);

				for (uint16_t i = 0; i < currentBufferLength; i++)
				{
					frame.data[i] = currentBuffer[i];
				}

				Can::sendMessage(frame);
			}
			else
			{
				for (; currentFrameId < currentFrameCount; currentFrameId++)
				{
					uint16_t len = 8;
					if (currentFrameId == currentFrameCount - 1)
					{
						len = currentBufferLength - currentFrameId * 7 + 1;
					}

					modm::can::Message frame(generateCurrentFrameIdentifier(), len);
					frame.setExtended(true);
					frame.data[0] = currentFrameId ? currentFrameId & 0xff : currentFrameCount & 0xff;

					for (uint16_t i = 1; i < len; i++)
					{
						frame.data[i] = currentBuffer[currentFrameId * 7 + i - 1];
					}

					Can::sendMessage(frame);
				}
			}

			RF_END();
		}
	}
}
