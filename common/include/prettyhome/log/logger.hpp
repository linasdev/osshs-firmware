/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_LOGGER_HPP
#define PRETTYHOME_LOGGER_HPP

#include <prettyhome/log/log_prefixer.hpp>

namespace prettyhome
{
	namespace log
	{
		extern modm::log::Logger logger;
	}
}

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define PRETTYHOME_ENABLE_LOGGER(device, behavior) \
	modm::IODeviceWrapper< device, behavior > loggerDevice; \
	modm::log::Logger prettyhome::log::logger(loggerDevice);

#define PRETTYHOME_PREFIXED_LOGGER(level) prettyhome::log::LogPrefixer::writePrefix< level, __LINE__ >(prettyhome::log::logger, __FILENAME__, __PRETTY_FUNCTION__)

#define PRETTYHOME_LOGGER \
	if ( false ){} \
	else prettyhome::log::logger

#define PRETTYHOME_LOG_OFF_STREAM \
	if ( true ){}	\
	else PRETTYHOME_PREFIXED_LOGGER(modm::log::DISABLED)

#define PRETTYHOME_LOG_DEBUG_STREAM \
	if (MODM_LOG_LEVEL > modm::log::DEBUG){} \
	else PRETTYHOME_PREFIXED_LOGGER(modm::log::DEBUG)

#define PRETTYHOME_LOG_INFO_STREAM \
	if (MODM_LOG_LEVEL > modm::log::INFO){}	\
	else PRETTYHOME_PREFIXED_LOGGER(modm::log::INFO)

#define PRETTYHOME_LOG_WARNING_STREAM \
	if (MODM_LOG_LEVEL > modm::log::WARNING){}	\
	else PRETTYHOME_PREFIXED_LOGGER(modm::log::WARNING)

#define PRETTYHOME_LOG_ERROR_STREAM \
	if (MODM_LOG_LEVEL > modm::log::ERROR){}	\
	else PRETTYHOME_PREFIXED_LOGGER(modm::log::ERROR)

#define PRETTYHOME_LOG_OFF(str) PRETTYHOME_LOG_OFF_STREAM << str << "\r\n";
#define PRETTYHOME_LOG_DEBUG(str) PRETTYHOME_LOG_DEBUG_STREAM << str << "\r\n";
#define PRETTYHOME_LOG_INFO(str) PRETTYHOME_LOG_INFO_STREAM << str << "\r\n";
#define PRETTYHOME_LOG_WARNING(str) PRETTYHOME_LOG_WARNING_STREAM << str << "\r\n";
#define PRETTYHOME_LOG_ERROR(str) PRETTYHOME_LOG_ERROR_STREAM << str << "\r\n";

#define PRETTYHOME_LOG_CLEAN() PRETTYHOME_LOGGER << "\033[2J\033[H";

#endif
