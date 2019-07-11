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
		template < typename I2cMaster >
		uint8_t
		EepromModule< I2cMaster >::getModuleTypeId() const
		{
			return static_cast< uint8_t >(static_cast< uint16_t > (events::EepromEvent::BASE_EVENT) >> 8);
		}

		template < typename I2cMaster >
		bool
		EepromModule< I2cMaster >::run()
		{
      PT_BEGIN();

			do
			{
				PT_WAIT_UNTIL(!eventQueue.empty());

				currentEvent = eventQueue.front();
				eventQueue.pop();

				if (currentEvent->getType() == static_cast< uint16_t >(events::EepromEvent::REQUEST_DATA_EVENT))
				{
					PT_CALL(handleRequestDataEvent(std::static_pointer_cast< events::EepromRequestDataEvent >(currentEvent)));
				}
				else if (currentEvent->getType() == static_cast< uint16_t >(events::EepromEvent::UPDATE_DATA_EVENT))
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

		bool test(bool locked)
		{
			PRETTYHOME_LOG_INFO << "ASDASDASD" << locked << "\r\n";
			return true;
		}

		bool lockeda(bool reset = false, bool set = false)
		{
			static volatile bool locked = false;
			if (reset)
				locked = false;
			if (set)
				locked = true;
			return locked;
		}

		template < typename I2cMaster >
		modm::ResumableResult<void>
		EepromModule< I2cMaster >::handleRequestDataEvent(std::shared_ptr< events::EepromRequestDataEvent > event)
		{
			// static volatile bool locked = false;
			RF_BEGIN(0);

			currentData.reset(new uint8_t[event->getDataLen()]);

			// RF_WAIT_WHILE(test(locked) && locked);
			// RF_WAIT_WHILE(lockeda(false, false));
			// lockeda(false, true);
			RF_WAIT_UNTIL(ResourceLock< modm::platform::I2cMaster1 >::tryLock());
			currentSuccess = RF_CALL(i2cEeprom.read(event->getAddress(), currentData.get(), event->getDataLen()));
			ResourceLock< modm::platform::I2cMaster1 >::unlock();
			// lockeda(true, false)
			static std::shared_ptr< events::Event > responseEvent;

			if (currentSuccess)
			{
				events::EepromDataReadyEvent *successEvent = new events::EepromDataReadyEvent(currentData, event->getDataLen(), event->getCauseId());
				responseEvent.reset(static_cast< events::Event* > (successEvent));
			}
			else
			{
				events::EepromErrorEvent *errorEvent = new events::EepromErrorEvent(0x00, event->getCauseId());
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

		template < typename I2cMaster >
		modm::ResumableResult<void>
		EepromModule< I2cMaster >::handleUpdateDataEvent(std::shared_ptr< events::EepromUpdateDataEvent > event)
		{
			RF_BEGIN(1);

			currentData = event->getData();

			// RF_WAIT_UNTIL(ResourceLock< modm::platform::I2cMaster1 >::tryLock());
			currentSuccess = RF_CALL(i2cEeprom.write(event->getAddress(), currentData.get(), event->getDataLen()));
			// ResourceLock< modm::platform::I2cMaster1 >::unlock();

			static std::shared_ptr< events::Event > responseEvent;

			if (currentSuccess)
			{
				events::EepromUpdateSuccessEvent *successEvent = new events::EepromUpdateSuccessEvent(event->getCauseId());
				responseEvent.reset(static_cast< events::Event* > (successEvent));
			}
			else
			{
				events::EepromErrorEvent *errorEvent = new events::EepromErrorEvent(0x00, event->getCauseId());
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

			writeCycleTimeout.restart(5);
			RF_WAIT_UNTIL(writeCycleTimeout.isExpired());

			RF_END();
		}
	}
}