/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_PWM_MODULE_HPP
  #error	"Don't include this file directly, use 'pwm_module.hpp' instead!"
#endif

#include <prettyhome/resource_lock.hpp>

namespace prettyhome
{
	namespace modules
	{
 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		PwmModule< channels, SpiMaster, Xlat, Xblank >::PwmModule()
		{
			tlc594x.initialize(0x000, -1, true, false, true);
		}

		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		uint8_t
		PwmModule< channels, SpiMaster, Xlat, Xblank >::getModuleTypeId() const
		{
			return static_cast< uint8_t >(static_cast< uint16_t > (events::PwmEvent::BASE) >> 8);
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		bool
		PwmModule< channels, SpiMaster, Xlat, Xblank >::run()
		{
      PT_BEGIN();

			do
			{
				PT_WAIT_WHILE(eventQueue.empty());

				currentEvent = eventQueue.front();
				eventQueue.pop();

				if (currentEvent->getType() == static_cast< uint16_t >(events::PwmEvent::REQUEST_STATUS))
				{
					PT_CALL(handleRequestStatusEvent(std::static_pointer_cast< events::PwmRequestStatusEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::PwmEvent::ENABLE))
				{
					PT_CALL(handleEnableEvent(std::static_pointer_cast< events::PwmEnableEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::PwmEvent::DISABLE))
				{
					PT_CALL(handleDisableEvent(std::static_pointer_cast< events::PwmDisableEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::PwmEvent::REQUEST_CHANNEL))
				{
					PT_CALL(handleRequestChannelEvent(std::static_pointer_cast< events::PwmRequestChannelEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::PwmEvent::UPDATE_CHANNEL))
				{
					PT_CALL(handleUpdateChannelEvent(std::static_pointer_cast< events::PwmUpdateChannelEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::PwmEvent::REQUEST_RGBW_CHANNEL))
				{
					PT_CALL(handleRequestRgbwChannelEvent(std::static_pointer_cast< events::PwmRequestRgbwChannelEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::PwmEvent::UPDATE_RGBW_CHANNEL))
				{
					PT_CALL(handleUpdateRgbwChannelEvent(std::static_pointer_cast< events::PwmUpdateRgbwChannelEvent >(currentEvent)));
				}

				currentEvent.reset();
			}
			while (true);

      PT_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleRequestStatusEvent(std::shared_ptr< events::PwmRequestStatusEvent > event)
		{
			RF_BEGIN();

			static std::shared_ptr< events::Event > responseEvent(static_cast< events::Event* > (new events::PwmStatusReadyEvent(
				tlc594x.isEnabled() ? events::PwmStatus::ENABLED : events::PwmStatus::DISABLED,
				event->getCauseId(),
				[=](std::shared_ptr< prettyhome::events::Event > event) -> void
				{
						this->handleEvent(event);
				}
			)));

			if (event->getCallback() != nullptr)
			{
				event->getCallback()(responseEvent);
			}
			else
			{
				System::reportEvent(responseEvent);
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleEnableEvent(std::shared_ptr< events::PwmEnableEvent > event)
		{
			RF_BEGIN();

			tlc594x.enable();

			static std::shared_ptr< events::Event > responseEvent(static_cast< events::Event* > (new events::PwmStatusReadyEvent(
				tlc594x.isEnabled() ? events::PwmStatus::ENABLED : events::PwmStatus::DISABLED,
				event->getCauseId(),
				[=](std::shared_ptr< prettyhome::events::Event > event) -> void
				{
						this->handleEvent(event);
				}
			)));

			if (event->getCallback() != nullptr)
			{
				event->getCallback()(responseEvent);
			}
			else
			{
				System::reportEvent(responseEvent);
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleDisableEvent(std::shared_ptr< events::PwmDisableEvent > event)
		{
			RF_BEGIN();

			tlc594x.disable();

			static std::shared_ptr< events::Event > responseEvent(static_cast< events::Event* > (new events::PwmStatusReadyEvent(
				tlc594x.isEnabled() ? events::PwmStatus::ENABLED : events::PwmStatus::DISABLED,
				event->getCauseId(),
				[=](std::shared_ptr< prettyhome::events::Event > event) -> void
				{
						this->handleEvent(event);
				}
			)));

			if (event->getCallback() != nullptr)
			{
				event->getCallback()(responseEvent);
			}
			else
			{
				System::reportEvent(responseEvent);
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleRequestChannelEvent(std::shared_ptr< events::PwmRequestChannelEvent > event)
		{
			RF_BEGIN();

			static std::shared_ptr< events::Event > responseEvent;

			if (event->getChannel() < channels)
			{
				events::PwmChannelReadyEvent *successEvent = new events::PwmChannelReadyEvent(
					event->getChannel(),
					tlc594x.getChannel(event->getChannel()),
					event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
					{
							this->handleEvent(event);
					}
				);

				responseEvent.reset(static_cast< events::Event* > (successEvent));
			}
			else
			{
				events::PwmErrorEvent *errorEvent = new events::PwmErrorEvent(
					events::PwmError::CHANNEL_OUT_OF_BOUNDS,
					event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
					{
							this->handleEvent(event);
					}
				);

				responseEvent.reset(static_cast< events::Event* > (errorEvent));
			}

			if (event->getCallback() != nullptr)
			{
				event->getCallback()(responseEvent);
			}
			else
			{
				System::reportEvent(responseEvent);
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleUpdateChannelEvent(std::shared_ptr< events::PwmUpdateChannelEvent > event)
		{
			RF_BEGIN();

			if (event->getChannel() < channels && event->getValue() <= 0xfff)
			{
				tlc594x.setChannel(event->getChannel(), event->getValue());

				RF_WAIT_UNTIL(ResourceLock< SpiMaster >::tryLock());
				RF_CALL(tlc594x.writeChannels());
				ResourceLock< SpiMaster >::unlock();
			}

			static std::shared_ptr< events::Event > responseEvent;

			if (event->getChannel() < channels)
			{
				if (event->getValue() <= 0xfff)
				{
					events::PwmUpdateSuccessEvent *successEvent = new events::PwmUpdateSuccessEvent(
						event->getCauseId(),
						[=](std::shared_ptr< prettyhome::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					responseEvent.reset(static_cast< events::Event* > (successEvent));
				}
				else
				{
					events::PwmErrorEvent *errorEvent = new events::PwmErrorEvent(
						events::PwmError::VALUE_OUT_OF_BOUNDS,
						event->getCauseId(),
						[=](std::shared_ptr< prettyhome::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					responseEvent.reset(static_cast< events::Event* > (errorEvent));
				}
			}
			else
			{
				events::PwmErrorEvent *errorEvent = new events::PwmErrorEvent(
					events::PwmError::CHANNEL_OUT_OF_BOUNDS,
					event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
					{
							this->handleEvent(event);
					}
				);

				responseEvent.reset(static_cast< events::Event* > (errorEvent));
			}

			if (event->getCallback() != nullptr)
			{
				event->getCallback()(responseEvent);
			}
			else
			{
				System::reportEvent(responseEvent);
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleRequestRgbwChannelEvent(std::shared_ptr< events::PwmRequestRgbwChannelEvent > event)
		{
			RF_BEGIN();

			static std::shared_ptr< events::Event > responseEvent;

			if (event->getChannel() * 4 + 3 < channels)
			{
				events::PwmRgbwValue value(
					tlc594x.getChannel(event->getChannel() * 4 + 0),
					tlc594x.getChannel(event->getChannel() * 4 + 1),
					tlc594x.getChannel(event->getChannel() * 4 + 2),
					tlc594x.getChannel(event->getChannel() * 4 + 3)
				);

				events::PwmRgbwChannelReadyEvent *successEvent = new events::PwmRgbwChannelReadyEvent(
					event->getChannel(),
					value,
					event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
					{
							this->handleEvent(event);
					}
				);

				responseEvent.reset(static_cast< events::Event* > (successEvent));
			}
			else
			{
				events::PwmErrorEvent *errorEvent = new events::PwmErrorEvent(
					events::PwmError::CHANNEL_OUT_OF_BOUNDS,
					event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
					{
							this->handleEvent(event);
					}
				);

				responseEvent.reset(static_cast< events::Event* > (errorEvent));
			}

			if (event->getCallback() != nullptr)
			{
				event->getCallback()(responseEvent);
			}
			else
			{
				System::reportEvent(responseEvent);
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleUpdateRgbwChannelEvent(std::shared_ptr< events::PwmUpdateRgbwChannelEvent > event)
		{
			RF_BEGIN();

			if (event->getChannel() * 4 + 3 < channels &&
					event->getValue().red 	<= 0xfff &&
					event->getValue().green <= 0xfff &&
					event->getValue().blue 	<= 0xfff &&
					event->getValue().white <= 0xfff)
			{
				tlc594x.setChannel(event->getChannel() * 4 + 0, event->getValue().red);
				tlc594x.setChannel(event->getChannel() * 4 + 1, event->getValue().green);
				tlc594x.setChannel(event->getChannel() * 4 + 2, event->getValue().blue);
				tlc594x.setChannel(event->getChannel() * 4 + 3, event->getValue().white);

				RF_WAIT_UNTIL(ResourceLock< SpiMaster >::tryLock());
				RF_CALL(tlc594x.writeChannels());
				ResourceLock< SpiMaster >::unlock();
			}

			static std::shared_ptr< events::Event > responseEvent;

			if (event->getChannel() * 4 + 3 < channels)
			{
				events::PwmRgbwValue value = event->getValue();
				if (value.red <= 0xfff && value.green <= 0xfff && value.blue <= 0xfff && value.white <= 0xfff)
				{
					events::PwmUpdateSuccessEvent *successEvent = new events::PwmUpdateSuccessEvent(
						event->getCauseId(),
						[=](std::shared_ptr< prettyhome::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					responseEvent.reset(static_cast< events::Event* > (successEvent));
				}
				else
				{
					events::PwmErrorEvent *errorEvent = new events::PwmErrorEvent(
						events::PwmError::VALUE_OUT_OF_BOUNDS,
						event->getCauseId(),
						[=](std::shared_ptr< prettyhome::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					responseEvent.reset(static_cast< events::Event* > (errorEvent));
				}
			}
			else
			{
				events::PwmErrorEvent *errorEvent = new events::PwmErrorEvent(
					events::PwmError::CHANNEL_OUT_OF_BOUNDS,
					event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
					{
							this->handleEvent(event);
					}
				);

				responseEvent.reset(static_cast< events::Event* > (errorEvent));
			}

			if (event->getCallback() != nullptr)
			{
				event->getCallback()(responseEvent);
			}
			else
			{
				System::reportEvent(responseEvent);
			}

			RF_END();
		}
	}
}