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

#include <osshs/modules/module.hpp>
#include <osshs/system.hpp>
#include <osshs/log/logger.hpp>

namespace osshs
{
	namespace modules
	{
		void
		Module::initialize()
		{
			OSSHS_LOG_INFO("Initializing module.");

			System::subscribeEvent(events::EventSelector(0xff00, static_cast<uint16_t>(getModuleTypeId()) << 8),
				[=](std::shared_ptr<events::Event> event) -> void
				{
					this->handleEvent(event);
				}
			);
		}

		void
		Module::handleEvent(std::shared_ptr<events::Event> event)
		{
			OSSHS_LOG_DEBUG("Handling event(type = 0x%04x).", event->getType());

			eventQueue.push(event);
		}
	}
}
