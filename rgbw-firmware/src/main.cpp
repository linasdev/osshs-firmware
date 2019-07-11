/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/log/logger.hpp>
#include <prettyhome/system.hpp>
#include <prettyhome/modules/eeprom_module.hpp>
#include <prettyhome/time.hpp>

#include "./board.hpp"

using namespace modm::literals;

#undef	MODM_LOG_LEVEL
#define	MODM_LOG_LEVEL modm::log::DEBUG

PRETTYHOME_ENABLE_LOGGER(modm::platform::Usart1, modm::IOBuffer::BlockIfFull);

// void
// wait(uint32_t millis)
// {
// 	uint32_t start = prettyhome::Time::getSystemTime< uint32_t, prettyhome::Time::Precision::Milliseconds > ();
// 	while (start + millis > prettyhome::Time::getSystemTime< uint32_t, prettyhome::Time::Precision::Milliseconds > ());
// }

int
main()
{
	// for (uint64_t i = 0; i < 3000000000; i++) __asm__("nop");
	prettyhome::board::initialize();

	modm::platform::Usart1::connect<modm::platform::GpioA9::Tx>();
	modm::platform::Usart1::initialize<prettyhome::board::SystemClock, 115200_Bd>();

	modm::platform::I2cMaster1::connect<modm::platform::GpioB6::Scl, modm::platform::GpioB7::Sda> ();
	modm::platform::I2cMaster1::initialize<prettyhome::board::SystemClock, 360_kBd>();

	PRETTYHOME_LOG_CLEAN();

	prettyhome::System::initialize();
	prettyhome::System::registerModule(new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >());
	prettyhome::System::registerModule(new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >());
	// prettyhome::System::registerModule(new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >());
	// prettyhome::System::registerModule(new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >());
	// prettyhome::System::registerModule(new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >());
	// prettyhome::System::registerModule(new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >());
	// prettyhome::System::registerModule(new prettyhome::modules::EepromModule< modm::platform::I2cMaster1 >());
#define LEN 1
	prettyhome::events::EepromRequestDataEvent *event0 = new prettyhome::events::EepromRequestDataEvent(0x0000, LEN, [] (std::shared_ptr< prettyhome::events::Event > event) -> void
	{
		prettyhome::events::EepromDataReadyEvent *res = static_cast< prettyhome::events::EepromDataReadyEvent* > (event.get());
		// std::shared_ptr< uint8_t[] > newData(new uint8_t[res->getDataLen()]);

		for (uint8_t i = 0; i < res->getDataLen(); i++) {
			// newData[i] = res->getData()[i] + 1;
			PRETTYHOME_LOG_INFO << "OLD " << i << ": " << res->getData()[i] << "\r\n";
		}



		prettyhome::events::EepromUpdateDataEvent *event1 = new prettyhome::events::EepromUpdateDataEvent(0x0000, res->getData(), LEN, [] (std::shared_ptr< prettyhome::events::Event > event) -> void
		{
			prettyhome::events::EepromRequestDataEvent *event2 = new prettyhome::events::EepromRequestDataEvent(0x0000, LEN, [] (std::shared_ptr< prettyhome::events::Event > event) -> void
			{
				prettyhome::events::EepromDataReadyEvent *res = static_cast< prettyhome::events::EepromDataReadyEvent* > (event.get());
				for (uint8_t i = 0; i < res->getDataLen(); i++) {
					PRETTYHOME_LOG_INFO << "NEW " << i << ": " << res->getData()[i] << "\r\n";
				}
			});

			prettyhome::System::reportEvent(std::shared_ptr< prettyhome::events::Event >(static_cast< prettyhome::events::Event* > (event2)));
		});

		prettyhome::System::reportEvent (std::shared_ptr< prettyhome::events::Event >(static_cast< prettyhome::events::Event* > (event1)));
	});

	prettyhome::System::reportEvent(std::shared_ptr< prettyhome::events::Event >(static_cast< prettyhome::events::Event* > (event0)));

	prettyhome::System::loop();
	// prettyhome::events::EepromRequestDataEvent ev(0x0000, 1);

	// modm::I2cEeprom< modm::platform::I2cMaster1 > i2cEeprom;


	// if (this.callback == nullptr)
	// 	return false;
	//
	// Event formChannelEvent(FORM_CHANNEL_EVENT, causeId, nullptr, 0, callback, false);
	// this->callback(formChannelEvent);
	//
	// return true;
	// do
	// {

		// uint64_t readData = 0;
		// RF_CALL_BLOCKING(i2cEeprom.read(0x0000, (uint8_t *)&readData, 8));
		// wait(50);

		// uint64_t writeData = readData + 1;
		// RF_CALL_BLOCKING(i2cEeprom.write(0x0000, (uint8_t *)&writeData, 8));
		// wait(50);

		// PRETTYHOME_LOG_INFO << readData << "\r\n";
	// prettyhome::System::reportEvent(ev);

		// wait(2000);
	// } while (true);

	return 0;
}