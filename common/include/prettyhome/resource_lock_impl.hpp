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
	#error "Don't include this file directly, use 'resource_lock.hpp' instead!"
#endif

namespace prettyhome
{
	template< typename Resource >
	bool ResourceLock< Resource >::locked = false;

	template< typename Resource >
	bool
	ResourceLock< Resource >::tryLock()
	{
		if (ResourceLock< Resource >::locked)
			return false;

		ResourceLock< Resource >::locked = true;
		return true;
	}

	template< typename Resource >
	void
	ResourceLock< Resource >::unlock()
	{
		ResourceLock< Resource >::locked = false;
	}
}
