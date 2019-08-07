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

#include <cstdint>

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

		/**
		 * @brief Initialize system time.
		 * 
		 */
		static void
		initialize();

		/**
		 * @brief System time getter.
		 * 
		 * @tparam T return type.
		 * @tparam precision Either Precision::Milliseconds or Precision::Seconds.
		 * @return T system time.
		 */
		template< typename T, Precision precision >
		static T
		getSystemTime();
	private:
		static uint64_t systemTime;

		/**
		 * @brief Increment system time. Called from interrupt.
		 * 
		 */
		static void
		tick();
	};
}

#include <prettyhome/time_impl.hpp>

#endif  // PRETTYHOME_TIME_HPP
