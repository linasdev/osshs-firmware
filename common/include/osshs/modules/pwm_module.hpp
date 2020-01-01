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
#define OSSHS_PWM_MODULE_HPP

#include <modm/driver/pwm/tlc594x.hpp>
#include <osshs/modules/module.hpp>
#include <osshs/events/pwm_event.hpp>

namespace osshs
{
	namespace modules
	{
 		template <uint16_t channels, typename SpiMaster, typename Xlat, typename Xblank>
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
			modm::TLC594X<channels, SpiMaster, Xlat, Xblank> tlc594x;

			std::shared_ptr<events::Event> currentEvent;

			modm::ResumableResult<void>
			handleRequestStatusEvent(std::shared_ptr<events::PwmRequestStatusEvent> event);

			modm::ResumableResult<void>
			handleEnableEvent(std::shared_ptr<events::PwmEnableEvent> event);

			modm::ResumableResult<void>
			handleDisableEvent(std::shared_ptr<events::PwmDisableEvent> event);

			modm::ResumableResult<void>
			handleRequestChannelEvent(std::shared_ptr<events::PwmRequestChannelEvent> event);

			modm::ResumableResult<void>
			handleUpdateChannelEvent(std::shared_ptr<events::PwmUpdateChannelEvent> event);

			modm::ResumableResult<void>
			handleRequestRgbwChannelEvent(std::shared_ptr<events::PwmRequestRgbwChannelEvent> event);

			modm::ResumableResult<void>
			handleUpdateRgbwChannelEvent(std::shared_ptr<events::PwmUpdateRgbwChannelEvent> event);
	  };
	}
}

#include <osshs/modules/pwm_module_impl.hpp>

#endif  // OSSHS_PWM_MODULE_HPP
