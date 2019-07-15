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
#define PRETTYHOME_PWM_MODULE_HPP

#include <modm/driver/pwm/tlc594x.hpp>
#include <prettyhome/modules/module.hpp>
#include <prettyhome/events/pwm_event.hpp>

namespace prettyhome
{
	namespace modules
	{
 		template < uint16_t CHANNELS, typename SpiMaster, typename Xlat, typename Xblank >
		class PwmModule : public Module, private modm::NestedResumable<1>
		{
		public:
			PwmModule();

			uint8_t
			getModuleTypeId() const;
		protected:
			bool
			run();
		private:
			modm::TLC594X< CHANNELS, SpiMaster, Xlat, Xblank > tlc594x;

			std::shared_ptr< events::Event > currentEvent;

			modm::ResumableResult<void>
			handleRequestStatusEvent(std::shared_ptr< events::PwmRequestStatusEvent > event);

			modm::ResumableResult<void>
			handleEnableEvent(std::shared_ptr< events::PwmEnableEvent > event);

			modm::ResumableResult<void>
			handleDisableEvent(std::shared_ptr< events::PwmDisableEvent > event);

			modm::ResumableResult<void>
			handleRequestChannelEvent(std::shared_ptr< events::PwmRequestChannelEvent > event);

			modm::ResumableResult<void>
			handleUpdateChannelEvent(std::shared_ptr< events::PwmUpdateChannelEvent > event);

			modm::ResumableResult<void>
			handleRequestRgbwChannelEvent(std::shared_ptr< events::PwmRequestRgbwChannelEvent > event);

			modm::ResumableResult<void>
			handleUpdateRgbwChannelEvent(std::shared_ptr< events::PwmUpdateRgbwChannelEvent > event);
	  };
	}
}

#include <prettyhome/modules/pwm_module_impl.hpp>

#endif  // PRETTYHOME_PWM_MODULE_HPP