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

#ifndef OSSHS_LOG_PREFIXER_HPP
#define OSSHS_LOG_PREFIXER_HPP

#include <modm/debug/logger.hpp>

namespace osshs
{
	namespace log
	{
		class LogPrefixer
		{
		public:
			/**
			 * @brief Write a log message prefix to a stream.
			 * 
			 * @tparam level severity level. One of: modm::log::DISABLED, modm::log::DEBUG, modm::log::INFO, modm::log::WARNING or modm::log::ERROR.
			 * @tparam line line from which the message was logged. Usually __LINE__.
			 * @param stream stream to which the prefix should be written.
			 * @param file File file from which the message was logged. Usually __FILENAME__.
			 * @return modm::IOStream& stream to which the prefix was written.
			 */
			template< modm::log::Level level, uint32_t line >
			static modm::IOStream&
			writePrefix(modm::IOStream &stream, const char *file);
		};
	}
}

#include <osshs/log/log_prefixer_impl.hpp>

#endif  // OSSHS_LOG_PREFIXER_HPP
