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
	#error "Don't include this file directly, use 'log_prefixer.hpp' instead!"
#endif

#include <prettyhome/time.hpp>

namespace prettyhome
{
	namespace log
	{
		template< modm::log::Level level, uint32_t line >
		modm::IOStream&
		LogPrefixer::writePrefix(modm::IOStream &stream, const char* file)
		{
			stream << '[';
			stream << prettyhome::Time::getSystemTime< float, prettyhome::Time::Precision::Seconds >();
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