/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_EEPROM_MODULE_HPP
  #error	"Don't include this file directly, use 'eeprom_module.hpp' instead!"
#endif

#include <prettyhome/resource_lock.hpp>

namespace prettyhome
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
				else
				{

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

			currentData.reset(new uint8_t[event->getDataLen()]);

			RF_WAIT_UNTIL(ResourceLock< I2cMaster >::tryLock());
			currentSuccess = RF_CALL(i2cEeprom.read(event->getAddress(), currentData.get(), event->getDataLen()));
			ResourceLock< I2cMaster >::unlock();

			static std::shared_ptr< events::Event > responseEvent;

			if (currentSuccess)
			{
				events::EepromDataReadyEvent *successEvent = new events::EepromDataReadyEvent(currentData, event->getDataLen(), event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
				{
						this->handleEvent(event);
				});
				responseEvent.reset(static_cast< events::Event* > (successEvent));
			}
			else
			{
				events::EepromErrorEvent *errorEvent = new events::EepromErrorEvent(events::EepromErrorEvent::READ_FAILED, event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
				{
						this->handleEvent(event);
				});
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

			RF_END();
		}

		template < typename I2cMaster, uint16_t writeCycleTime >
		modm::ResumableResult<void>
		EepromModule< I2cMaster, writeCycleTime >::handleUpdateDataEvent(std::shared_ptr< events::EepromUpdateDataEvent > event)
		{
			RF_BEGIN();

			currentData = event->getData();

			RF_WAIT_UNTIL(ResourceLock< I2cMaster >::tryLock());
			currentSuccess = RF_CALL(i2cEeprom.write(event->getAddress(), currentData.get(), event->getDataLen()));

			static std::shared_ptr< events::Event > responseEvent;

			if (currentSuccess)
			{
				events::EepromUpdateSuccessEvent *successEvent = new events::EepromUpdateSuccessEvent(event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
				{
						this->handleEvent(event);
				});
				responseEvent.reset(static_cast< events::Event* > (successEvent));
			}
			else
			{
				events::EepromErrorEvent *errorEvent = new events::EepromErrorEvent(events::EepromErrorEvent::WRITE_FAILED, event->getCauseId(),
					[=](std::shared_ptr< prettyhome::events::Event > event) -> void
				{
						this->handleEvent(event);
				});
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

			writeCycleTimeout.restart(writeCycleTime);
			RF_WAIT_UNTIL(writeCycleTimeout.isExpired());
			writeCycleTimeout.stop();
			ResourceLock< I2cMaster >::unlock();

			RF_END();
		}
	}
}