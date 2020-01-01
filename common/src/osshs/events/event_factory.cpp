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

#include <osshs/events/event_factory.hpp>
#include <osshs/log/logger.hpp>

namespace osshs
{
	namespace events
	{
		std::shared_ptr<Event>
		EventFactory::make(uint16_t type, std::unique_ptr<const uint8_t[]> data, EventCallback callback)
		{
			OSSHS_LOG_DEBUG("Making event(type = 0x%04x).", type);

			if (Event::eventRegister().find(type) == Event::eventRegister().end())
			{
				OSSHS_LOG_WARNING("Could not make event(type = 0x%04x).", type);
				return std::shared_ptr<Event>();
			}

			return Event::eventRegister().at(type)(std::move(data), callback);
		}
	}
}
