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

#ifndef OSSHS_EEPROM_MODULE_HPP
	#error "Don't include this file directly, use 'eeprom_module.hpp' instead!"
#endif

#include <osshs/resource_lock.hpp>
#include <osshs/log/logger.hpp>

namespace osshs
{
	namespace modules
	{
		template < typename I2cMaster, uint16_t writeCycleTime >
		uint8_t
		EepromModule< I2cMaster, writeCycleTime >::getModuleTypeId() const
		{
			return static_cast< uint8_t >(static_cast< uint16_t > (events::EepromEvent::BASE) >> 8);
		}

		template < typename I2cMaster, uint16_t writeCycleTime >
		bool
		EepromModule< I2cMaster, writeCycleTime >::run()
		{
      		PT_BEGIN();

			do
			{
				PT_WAIT_WHILE(eventQueue.empty());

				currentEvent = eventQueue.front();
				eventQueue.pop();

				if (currentEvent->getType() == static_cast< uint16_t >(events::EepromEvent::REQUEST_DATA))
				{
					PT_CALL(handleRequestDataEvent(std::static_pointer_cast< events::EepromRequestDataEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::EepromEvent::UPDATE_DATA))
				{
					PT_CALL(handleUpdateDataEvent(std::static_pointer_cast< events::EepromUpdateDataEvent >(currentEvent)));
				}

				currentEvent.reset();
			}
			while (true);

      		PT_END();
		}

		template < typename I2cMaster, uint16_t writeCycleTime >
		modm::ResumableResult<void>
		EepromModule< I2cMaster, writeCycleTime >::handleRequestDataEvent(std::shared_ptr< events::EepromRequestDataEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG_STREAM << "Handling request data event"
				<< "(address = " << event->getAddress()
				<< ", data_len = " << event->getDataLen()
				<< ").\r\n";

			currentData.reset(new (std::nothrow) uint8_t[event->getDataLen()]);

			if (currentData == nullptr)
			{
				OSSHS_LOG_ERROR_STREAM << "Failed to allocate memory for a buffer"
					<< "(buffer_length = " << event->getDataLen()
					<< ").\r\n";

				RF_RETURN();
			}

			RF_WAIT_UNTIL(ResourceLock< I2cMaster >::tryLock());
			currentSuccess = RF_CALL(i2cEeprom.read(event->getAddress(), currentData.get(), event->getDataLen()));
			ResourceLock< I2cMaster >::unlock();

			{
				std::shared_ptr< events::Event > responseEvent;

				if (currentSuccess)
				{
					events::EepromDataReadyEvent *successEvent = new (std::nothrow) events::EepromDataReadyEvent(
						currentData,
						event->getDataLen(),
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					if (successEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for an eeprom data ready event.");
						RF_RETURN();
					}

					responseEvent.reset(static_cast< events::Event* > (successEvent));
				}
				else
				{
					events::EepromErrorEvent *errorEvent = new (std::nothrow) events::EepromErrorEvent(
						events::EepromError::READ_FAILED,
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					if (errorEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for an eeprom error event.");
						RF_RETURN();
					}

					responseEvent.reset(static_cast< events::Event* > (errorEvent));
				}

				currentData.reset();

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

		template < typename I2cMaster, uint16_t writeCycleTime >
		modm::ResumableResult<void>
		EepromModule< I2cMaster, writeCycleTime >::handleUpdateDataEvent(std::shared_ptr< events::EepromUpdateDataEvent > event)
		{
			RF_BEGIN();

			OSSHS_LOG_DEBUG_STREAM << "Handling update data event"
				<< "(address = " << event->getAddress()
				<< ", data_len = " << event->getDataLen()
				<< ").\r\n";

			currentData = event->getData();

			RF_WAIT_UNTIL(ResourceLock< I2cMaster >::tryLock());
			currentSuccess = RF_CALL(i2cEeprom.write(event->getAddress(), currentData.get(), event->getDataLen()));
			writeCycleTimeout.restart(writeCycleTime);

			{
				std::shared_ptr< events::Event > responseEvent;

				if (currentSuccess)
				{
					events::EepromUpdateSuccessEvent *successEvent = new (std::nothrow) events::EepromUpdateSuccessEvent(
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					if (successEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for an eeprom update success event.");
						RF_RETURN();
					}

					responseEvent.reset(static_cast< events::Event* > (successEvent));
				}
				else
				{
					events::EepromErrorEvent *errorEvent = new (std::nothrow) events::EepromErrorEvent(
						events::EepromError::WRITE_FAILED,
						event->getCauseId(),
						[=](std::shared_ptr< osshs::events::Event > event) -> void
						{
								this->handleEvent(event);
						}
					);

					if (errorEvent == nullptr)
					{
						OSSHS_LOG_ERROR("Failed to allocate memory for an eeprom error event.");
						RF_RETURN();
					}

					responseEvent.reset(static_cast< events::Event* > (errorEvent));
				}

				currentData.reset();

				if (event->getCallback() != nullptr)
				{
					event->getCallback()(responseEvent);
				}
				else
				{
					System::reportEvent(responseEvent);
				}
			}

			RF_WAIT_UNTIL(writeCycleTimeout.isExpired());
			writeCycleTimeout.stop();
			ResourceLock< I2cMaster >::unlock();

			RF_END();
		}
	}
}
