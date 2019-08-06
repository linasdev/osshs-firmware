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
			template< modm::log::Level level, uint32_t line >
			static modm::IOStream&
			writePrefix(modm::IOStream &stream, const char *file);
		};
	}
}

#include <prettyhome/log/log_prefixer_impl.hpp>

#endif  // PRETTYHOME_LOG_PREFIXER_HPP
