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

#ifndef OSSHS_MODULE_HPP
#define OSSHS_MODULE_HPP

#include <cstdint>
#include <queue>

#include <modm/processing/protothread.hpp>
#include <modm/processing/resumable.hpp>
#include <osshs/events/event.hpp>

namespace osshs
{
	namespace modules
	{
		class ModuleManager;

		static constexpr uint8_t BASE_MODULE_ID = 0x00;

		class Module : public modm::pt::Protothread
		{
		public:
			Module() = default;

			/**
			 * @brief Module type id getter.
			 * 
			 * @return uint8_t module type id.
			 */
			virtual uint8_t
			getModuleTypeId() const = 0;
		protected:
			std::queue<std::shared_ptr<events::Event>> eventQueue;

			/**
			 * @brief Initialize the module. Should only be called from ModuleManager.
			 * 
			 */
			virtual void
			initialize();

			/**
			 * @brief Run module protothread.
			 * 
			 */
			virtual bool
			run() = 0;

			/**
			 * @brief Handle event.
			 * 
			 * @param event event to handle.
			 */
			void
			handleEvent(std::shared_ptr<events::Event> event);
		private:
			Module(const Module&) = delete;

			Module&
			operator=(const Module&) = delete;

			friend ModuleManager;
		};
	}
}

#endif  // OSSHS_MODULE_HPP
