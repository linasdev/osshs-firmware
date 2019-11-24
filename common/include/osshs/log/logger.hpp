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

#ifndef OSSHS_LOGGER_HPP
#define OSSHS_LOGGER_HPP

#include <osshs/log/log_prefixer.hpp>

namespace osshs
{
	namespace log
	{
		extern modm::log::Logger logger;
	}
}

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define OSSHS_ENABLE_LOGGER(device, behavior) \
	modm::IODeviceWrapper< device, behavior > loggerDevice; \
	modm::log::Logger osshs::log::logger(loggerDevice);

#define OSSHS_PREFIXED_LOGGER(level) osshs::log::LogPrefixer::writePrefix(osshs::log::logger, level, __FILENAME__, __LINE__)

#define OSSHS_LOGGER \
	if ( false ){} \
	else osshs::log::logger

#define OSSHS_LOG_OFF_STREAM \
	if ( true ){}	\
	else OSSHS_PREFIXED_LOGGER(modm::log::DISABLED)

#define OSSHS_LOG_DEBUG_STREAM \
	if (MODM_LOG_LEVEL > modm::log::DEBUG){} \
	else OSSHS_PREFIXED_LOGGER(modm::log::DEBUG)

#define OSSHS_LOG_INFO_STREAM \
	if (MODM_LOG_LEVEL > modm::log::INFO){}	\
	else OSSHS_PREFIXED_LOGGER(modm::log::INFO)

#define OSSHS_LOG_WARNING_STREAM \
	if (MODM_LOG_LEVEL > modm::log::WARNING){}	\
	else OSSHS_PREFIXED_LOGGER(modm::log::WARNING)

#define OSSHS_LOG_ERROR_STREAM \
	if (MODM_LOG_LEVEL > modm::log::ERROR){}	\
	else OSSHS_PREFIXED_LOGGER(modm::log::ERROR)

#define OSSHS_LOG_OFF(str) OSSHS_LOG_OFF_STREAM << str << "\r\n";
#define OSSHS_LOG_DEBUG(str) OSSHS_LOG_DEBUG_STREAM << str << "\r\n";
#define OSSHS_LOG_INFO(str) OSSHS_LOG_INFO_STREAM << str << "\r\n";
#define OSSHS_LOG_WARNING(str) OSSHS_LOG_WARNING_STREAM << str << "\r\n";
#define OSSHS_LOG_ERROR(str) OSSHS_LOG_ERROR_STREAM << str << "\r\n";

#define OSSHS_LOG_CLEAN() OSSHS_LOGGER << "\033[2J\033[H";

#endif
