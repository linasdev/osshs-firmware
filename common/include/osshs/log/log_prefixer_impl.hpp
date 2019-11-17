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
	#error "Don't include this file directly, use 'log_prefixer.hpp' instead!"
#endif

#include <osshs/time.hpp>

namespace osshs
{
	namespace log
	{
		template< modm::log::Level level, uint32_t line >
		modm::IOStream&
		LogPrefixer::writePrefix(modm::IOStream &stream, const char* file)
		{
			stream << '[';
			stream << osshs::Time::getSystemTime< float, osshs::Time::Precision::Seconds >();
			stream << ']';

			stream << '[';
			if constexpr(level == modm::log::DEBUG)
				stream << "DEBUG";
			if constexpr(level == modm::log::INFO)
				stream << "INFO";
			if constexpr(level == modm::log::WARNING)
				stream << "WARNING";
			if constexpr(level == modm::log::ERROR)
				stream << "ERROR";
			stream << ']';

			stream << '[';
			stream << file;
			stream << ':';
			stream << line;
			stream << ']';

			return stream;
		}
	}
}
