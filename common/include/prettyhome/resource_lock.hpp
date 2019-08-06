/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#ifndef PRETTYHOME_RESOURCE_LOCK_HPP
#define PRETTYHOME_RESOURCE_LOCK_HPP

namespace prettyhome
{
	template< typename Resource >
	class ResourceLock
	{
	public:
		static bool
		tryLock();

		static void
		unlock();
	private:
		static bool locked;
  };
}

#include <prettyhome/resource_lock_impl.hpp>

#endif  // PRETTYHOME_RESOURCE_LOCK_HPP
