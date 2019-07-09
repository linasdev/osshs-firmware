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
#define PRETTYHOME_TIME_HPP

#include <modm/platform.hpp>

namespace prettyhome
{
	class Time
	{
	public:
		enum class
		Precision
		{
			Milliseconds,
			Seconds
		};

		static void
		initialize();

		template< typename T, Precision precision >
		static T
		getSystemTime();
	private:
		static uint64_t systemTime;

		static void
		tick();
	};
}

#include <prettyhome/time_impl.hpp>

#endif  // PRETTYHOME_TIME_HPP