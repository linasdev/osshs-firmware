/*
 * MIT License
 *
 * Copyright (c) 2019 Linas Nikiperavicius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef OSSHS_PWM_MODULE_HPP
	#error "Don't include this file directly, use 'pwm_module.hpp' instead!"
#endif

#include <osshs/resource_lock.hpp>
#include <osshs/log/logger.hpp>

namespace osshs
{
	namespace modules
	{
 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		PwmModule< channels, SpiMaster, Xlat, Xblank >::PwmModule()
		{
			OSSHS_LOG_INFO("Initializing PWM module.");

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

			OSSHS_LOG_DEBUG("Handling request status event.");

			{
				std::shared_ptr< events::Event > responseEvent(static_cast< events::Event* > (new (std::nothrow) events::PwmStatusReadyEvent(
					tlc594x.isEnabled() ? events::PwmStatus::ENABLED : events::PwmStatus::DISABLED,
					event->getCauseId(),
					[=](std::shared_ptr< osshs::events::Event > event) -> void
					{
						this->handleEvent(event);
					}
				)));

				if (responseEvent == nullptr)
				{
					OSSHS_LOG_ERROR("Failed to allocate memory for a pwm status ready event.");
					RF_RETURN();
				}

				if (event->getCallback() != nullptr)
				{
					event->getCallback()(responseEvent);
				}
				else
				{
					System::reportEvent(responseEvent);
				}
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleEnableEvent(std::shared_ptr< events::PwmEnableEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG("Handling enable event.");

			tlc594x.enable();

			{
				std::shared_ptr< events::Event > responseEvent(static_cast< events::Event* > (new (std::nothrow) events::PwmStatusReadyEvent(
					tlc594x.isEnabled() ? events::PwmStatus::ENABLED : events::PwmStatus::DISABLED,
					event->getCauseId(),
					[=](std::shared_ptr< osshs::events::Event > event) -> void
					{
						this->handleEvent(event);
					}
				)));

				if (responseEvent == nullptr)
				{
					OSSHS_LOG_ERROR("Failed to allocate memory for a pwm status ready event.");
					RF_RETURN();
				}

				if (event->getCallback() != nullptr)
				{
					event->getCallback()(responseEvent);
				}
				else
				{
					System::reportEvent(responseEvent);
				}
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleDisableEvent(std::shared_ptr< events::PwmDisableEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG("Handling disable event.");

			tlc594x.disable();

			{
				std::shared_ptr< events::Event > responseEvent(static_cast< events::Event* > (new (std::nothrow) events::PwmStatusReadyEvent(
					tlc594x.isEnabled() ? events::PwmStatus::ENABLED : events::PwmStatus::DISABLED,
					event->getCauseId(),
					[=](std::shared_ptr< osshs::events::Event > event) -> void
					{
						this->handleEvent(event);
					}
				)));

				if (responseEvent == nullptr)
				{
					OSSHS_LOG_ERROR("Failed to allocate memory for a pwm status ready event.");
					RF_RETURN();
				}

				if (event->getCallback() != nullptr)
				{
					event->getCallback()(responseEvent);
				}
				else
				{
					System::reportEvent(responseEvent);
				}
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleRequestChannelEvent(std::shared_ptr< events::PwmRequestChannelEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG_STREAM << "Handling request channel event(channel = " << event->getChannel() << ").\r\n";

			{
				std::shared_ptr< events::Event > responseEvent;
				uint16_t channel = event->getChannel();

				if (channel < channels)
				{
					events::PwmChannelReadyEvent *successEvent = new (std::nothrow) events::PwmChannelReadyEvent(
						channel,
						tlc594x.getChannel(channel),
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
							this->handleEvent(event);
						}
					);

					if (successEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for a pwm channel ready event.");
						RF_RETURN();
					}

					responseEvent.reset(static_cast< events::Event* > (successEvent));
				}
				else
				{
					events::PwmErrorEvent *errorEvent = new (std::nothrow) events::PwmErrorEvent(
						events::PwmError::CHANNEL_OUT_OF_BOUNDS,
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
							this->handleEvent(event);
						}
					);

					if (errorEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for a pwm error event.");
						RF_RETURN();
					}

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
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleUpdateChannelEvent(std::shared_ptr< events::PwmUpdateChannelEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG_STREAM << "Handling update channel event"
				<< "(channel = " << event->getChannel()
				<< ", value = " << event->getValue()
				<< ").\r\n";

			if (event->getChannel() < channels && event->getValue() <= 0xfff)
			{
				tlc594x.setChannel(event->getChannel(), event->getValue());

				RF_WAIT_UNTIL(ResourceLock< SpiMaster >::tryLock());
				RF_CALL(tlc594x.writeChannels());
				ResourceLock< SpiMaster >::unlock();
			}

			{
				std::shared_ptr< events::Event > responseEvent;

				if (event->getChannel() < channels)
				{
					if (event->getValue() <= 0xfff)
					{
						events::PwmUpdateSuccessEvent *successEvent = new (std::nothrow) events::PwmUpdateSuccessEvent(
							event->getCauseId(),
							[=](std::shared_ptr< osshs::events::Event > event) -> void
							{
								this->handleEvent(event);
							}
						);

						if (successEvent == nullptr)
						{
							OSSHS_LOG_ERROR("Failed to allocate memory for a pwm udpate success event.");
							RF_RETURN();
						}

						responseEvent.reset(static_cast< events::Event* > (successEvent));
					}
					else
					{
						events::PwmErrorEvent *errorEvent = new (std::nothrow) events::PwmErrorEvent(
							events::PwmError::VALUE_OUT_OF_BOUNDS,
							event->getCauseId(),
							[=](std::shared_ptr< osshs::events::Event > event) -> void
							{
								this->handleEvent(event);
							}
						);

						if (errorEvent == nullptr)
						{
							OSSHS_LOG_ERROR("Failed to allocate memory for a pwm error event.");
							RF_RETURN();
						}

						responseEvent.reset(static_cast< events::Event* > (errorEvent));
					}
				}
				else
				{
					events::PwmErrorEvent *errorEvent = new (std::nothrow) events::PwmErrorEvent(
						events::PwmError::CHANNEL_OUT_OF_BOUNDS,
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
							this->handleEvent(event);
						}
					);

					if (errorEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for a pwm error event.");
						RF_RETURN();
					}

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
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleRequestRgbwChannelEvent(std::shared_ptr< events::PwmRequestRgbwChannelEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG_STREAM << "Handling request rgbw channel event(channel = " << event->getChannel() << ").\r\n";

			{
				std::shared_ptr< events::Event > responseEvent;
				uint16_t channel = event->getChannel() * 4;

				if (channel < channels)
				{
					events::PwmRgbwValue value(
						tlc594x.getChannel(channel + 0),
						tlc594x.getChannel(channel + 1),
						tlc594x.getChannel(channel + 2),
						tlc594x.getChannel(channel + 3)
					);

					events::PwmRgbwChannelReadyEvent *successEvent = new (std::nothrow) events::PwmRgbwChannelReadyEvent(
						event->getChannel(),
						value,
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
							this->handleEvent(event);
						}
					);

					if (successEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for a pwm rgbw channel ready event.");
						RF_RETURN();
					}

					responseEvent.reset(static_cast< events::Event* > (successEvent));
				}
				else
				{
					events::PwmErrorEvent *errorEvent = new (std::nothrow) events::PwmErrorEvent(
						events::PwmError::CHANNEL_OUT_OF_BOUNDS,
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
							this->handleEvent(event);
						}
					);

					if (errorEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for a pwm error event.");
						RF_RETURN();
					}

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
			}

			RF_END();
		}

 		template < uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank >
		modm::ResumableResult<void>
		PwmModule< channels, SpiMaster, Xlat, Xblank >::handleUpdateRgbwChannelEvent(std::shared_ptr< events::PwmUpdateRgbwChannelEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG_STREAM << "Handling update rgbw channel event"
				<< "(channel = " << event->getChannel()
				<< ", red = " << event->getValue().red
				<< ", green = " << event->getValue().green
				<< ", blue = " << event->getValue().blue
				<< ", white = " << event->getValue().white
				<< ").\r\n";

			if (event->getChannel() * 4 + 3 < channels &&
					event->getValue().red 	<= 0xfff &&
					event->getValue().green <= 0xfff &&
					event->getValue().blue 	<= 0xfff &&
					event->getValue().white <= 0xfff)
			{
				{
					uint16_t channel = event->getChannel() * 4;
					events::PwmRgbwValue value = event->getValue();

					tlc594x.setChannel(channel + 0, value.red);
					tlc594x.setChannel(channel + 1, value.green);
					tlc594x.setChannel(channel + 2, value.blue);
					tlc594x.setChannel(channel + 3, value.white);
				}

				RF_WAIT_UNTIL(ResourceLock< SpiMaster >::tryLock());
				RF_CALL(tlc594x.writeChannels());
				ResourceLock< SpiMaster >::unlock();
			}

			{
				std::shared_ptr< events::Event > responseEvent;

				if (event->getChannel() * 4 + 3 < channels)
				{
					events::PwmRgbwValue value = event->getValue();
					if (value.red <= 0xfff && value.green <= 0xfff && value.blue <= 0xfff && value.white <= 0xfff)
					{
						events::PwmUpdateSuccessEvent *successEvent = new (std::nothrow) events::PwmUpdateSuccessEvent(
							event->getCauseId(),
							[=](std::shared_ptr< osshs::events::Event > event) -> void
							{
								this->handleEvent(event);
							}
						);

						if (successEvent == nullptr)
						{
							OSSHS_LOG_ERROR("Failed to allocate memory for a pwm update success event.");
							RF_RETURN();
						}

						responseEvent.reset(static_cast< events::Event* > (successEvent));
					}
					else
					{
						events::PwmErrorEvent *errorEvent = new (std::nothrow) events::PwmErrorEvent(
							events::PwmError::VALUE_OUT_OF_BOUNDS,
							event->getCauseId(),
							[=](std::shared_ptr< osshs::events::Event > event) -> void
							{
								this->handleEvent(event);
							}
						);

						if (errorEvent == nullptr)
						{
							OSSHS_LOG_ERROR("Failed to allocate memory for a pwm error event.");
							RF_RETURN();
						}

						responseEvent.reset(static_cast< events::Event* > (errorEvent));
					}
				}
				else
				{
					events::PwmErrorEvent *errorEvent = new (std::nothrow) events::PwmErrorEvent(
						events::PwmError::CHANNEL_OUT_OF_BOUNDS,
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
							this->handleEvent(event);
						}
					);

					if (errorEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for a pwm error event.");
						RF_RETURN();
					}

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
			}

			RF_END();
		}
	}
}
