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

#ifndef OSSHS_EVENT_REGISTRAR_HPP
	#error "Don't include this file directly, use 'event_registrar.hpp' instead!"
#endif

namespace osshs
{
	namespace events
	{
		template<typename DerivedEvent>
		bool EventRegistrar<DerivedEvent>::registered = EventRegistrar<DerivedEvent>::registerDerivedEvent();

		template<typename DerivedEvent>
		bool
		EventRegistrar<DerivedEvent>::registerDerivedEvent()
		{
			Event::eventRegister()[DerivedEvent::TYPE] =
				[](std::unique_ptr<const uint8_t[]> data, EventCallback callback) -> std::shared_ptr<Event>
			{
				return std::make_shared<DerivedEvent>(std::move(data), callback);
			};

			return true;
		}

		template<typename DerivedEvent>
		EventRegistrar<DerivedEvent>::EventRegistrar(uint16_t causeId, EventCallback callback)
			: Event(DerivedEvent::TYPE, causeId, callback)
		{
			static_cast<void>(registered);
		}
	}
}
