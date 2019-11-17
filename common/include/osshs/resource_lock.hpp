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

#ifndef OSSHS_RESOURCE_LOCK_HPP
#define OSSHS_RESOURCE_LOCK_HPP

namespace osshs
{
	template< typename Resource >
	class ResourceLock
	{
	public:
		/**
		 * @brief Try to acquire a lock on the resource specified in the template.
		 * 
		 * @return true lock was acquired.
		 * @return false lock was not acquired.
		 */
		static bool
		tryLock();

		/**
		 * @brief Release a previously acquired lock.
		 * 
		 */
		static void
		unlock();
	private:
		static bool locked;
  };
}

#include <osshs/resource_lock_impl.hpp>

#endif  // OSSHS_RESOURCE_LOCK_HPP
