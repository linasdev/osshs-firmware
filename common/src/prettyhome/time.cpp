/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/time.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	uint64_t Time::systemTime = 0;

	void
	Time::initialize()
	{
		modm::platform::SysTickTimer::attachInterruptHandler(tick);
	}

	void
	Time::tick()
	{
		systemTime++;
	}
}