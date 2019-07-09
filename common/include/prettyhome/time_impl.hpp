/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_TIME_HPP
	#error	"Don't include this file directly, use 'time.hpp' instead!"
#endif

namespace prettyhome
{
	template< typename T, Time::Precision precision >
	T
	Time::getSystemTime()
	{
		modm::atomic::Lock lock;

		if constexpr (precision == Precision::Milliseconds)
			return static_cast< T >(systemTime);

		if constexpr (precision == Precision::Seconds)
			return static_cast< T >(systemTime) / 1000;
	}
}