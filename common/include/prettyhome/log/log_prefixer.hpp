/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_LOG_PREFIXER_HPP
#define PRETTYHOME_LOG_PREFIXER_HPP

#include <modm/debug/logger.hpp>

namespace prettyhome
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

#include <prettyhome/log/log_prefixer_impl.hpp>

#endif  // PRETTYHOME_LOG_PREFIXER_HPP
