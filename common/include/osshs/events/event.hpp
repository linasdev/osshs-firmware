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

#ifndef OSSHS_EVENT_HPP
#define OSSHS_EVENT_HPP

#include <functional>
#include <memory>
#include <unordered_map>

namespace osshs
{
	namespace events
	{
		class Event;

		typedef std::function< void (std::shared_ptr< Event >) > EventCallback;

		class Event
		{
		public:
			static constexpr uint16_t CAUSE_ID_GENERATE = static_cast< uint16_t >(-1);

			/**
			 * @brief Construct event.
			 * 
			 * @param type event type id.
			 * @param causeId event cause id.
			 * @param callback event callback.
			 */
			Event(uint16_t type, uint16_t causeId = CAUSE_ID_GENERATE, EventCallback callback = nullptr);

			/**
			 * @brief Type id getter.
			 * 
			 * @return uint16_t event type id.
			 */
			uint16_t
			getType() const;

			/**
			 * @brief Cause id getter.
			 * 
			 * @return uint16_t event cause id.
			 */
			uint16_t
			getCauseId() const;

			/**
			 * @brief Callback getter.
			 * 
			 * @return EventCallback event callback.
			 */
			EventCallback
			getCallback() const;

			/**
			 * @brief Serialize this event.
			 * 
			 * @return std::unique_ptr< const uint8_t[] > serialized event or nullptr if serialization failed.
			 */
			virtual std::unique_ptr< const uint8_t[] >
			serialize() const = 0;
		protected:
			uint16_t causeId;
		private:
			typedef std::function< std::shared_ptr< Event > (std::unique_ptr< const uint8_t[] >, EventCallback) > EventMaker;
			static uint16_t nextCauseId;
			uint16_t type;
			EventCallback callback;

			Event(const Event&) = delete;

			Event&
			operator=(const Event&) = delete;

			static std::unordered_map< uint16_t, EventMaker >&
			eventRegister();

			template< typename DerivedEvent >
			friend class EventRegistrar;

			friend class EventFactory;
		};
	}
}
#endif  // OSSHS_EVENT_HPP
