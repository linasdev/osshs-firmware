/*
 * Copyright (c) 2019, Linas Nikiperavicius
 *
 * This file is part of the PrettyHome project.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Linas Nikiperavicius <linas@linasdev.com>, 2019
 */

#include <prettyhome/interfaces/interface.hpp>
#include <prettyhome/log/logger.hpp>

namespace prettyhome
{
	namespace interfaces
	{
		void
		Interface::reportEventPacket(std::shared_ptr< EventPacket > eventPacket)
		{
			PRETTYHOME_LOG_DEBUG_STREAM << "Handling event packet"
				<< "(multi_target = "<< eventPacket->isMultiTarget()
				<< ", command = " << eventPacket->isCommand()
				<< ", transmitter_mac = " << eventPacket->getTransmitterMac()
				<< ", receiver_mac = " << eventPacket->getTransmitterMac()
				<< ", event_type = " << eventPacket->getEvent()->getType()
				<< ").\r\n";

			eventPacketQueue.push(eventPacket);
		}
	}
}
