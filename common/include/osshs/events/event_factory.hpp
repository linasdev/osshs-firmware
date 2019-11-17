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

#ifndef OSSHS_EVENT_FACTORY_HPP
#define OSSHS_EVENT_FACTORY_HPP

#include <osshs/events/event.hpp>

namespace osshs
{
	namespace events
	{
		class EventFactory
		{
		public:
			/**
			 * @brief Make event.
			 * 
			 * @param type event type.
			 * @param data serialized event.
			 * @param callback event callback.
			 * @return std::shared_ptr< Event > constructed event or nullptr if event could not be made.
			 */
			static std::shared_ptr< Event >
			make(uint16_t type, std::unique_ptr< const uint8_t[] > data, EventCallback callback = nullptr);
		};
	}
}

#endif  // OSSHS_EVENT_FACTORY_HPP
