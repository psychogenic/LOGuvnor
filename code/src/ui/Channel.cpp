/*
 * Channel.cpp
 *
 *  Created on: Nov 26, 2023
 *      Author: Pat Deegan
*  Copyright (C) 2023 Pat Deegan, https://psychogenic.com
*     This file is part of LOGuvnor.
*     LOGuvnor is free software: you can redistribute it and/or modify it under 
*     the terms of the GNU General Public License as published by the Free 
*     Software Foundation, either version 3 of the License, or (at your option)
*     any later version.
*  
*     LOGuvnor is distributed in the hope that it will be useful, but WITHOUT 
*     ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
*     FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
*     for more details.
*  
*     You should have received a copy of the GNU General Public License along 
*     with LOGuvnor. If not, see <https://www.gnu.org/licenses/>.
 */

#include "Channel.h"

namespace LOGuvnor {
namespace UI {

Channel::Channel(ChannelID cid, Pin indicateSelect, Pin indicateEnabled) :
		channelid(cid),
		ind_selected(indicateSelect, true),
		ind_enabled(indicateEnabled, true),
		freq(0),
		lastEditSelectedUnits(SELECTED_UNITS_NA)
{

}
Channel::Channel(const ChannelConfig & conf) :
				channelid(conf.cid),
				ind_selected(conf.indicateSelect, true),
				ind_enabled(conf.indicateEnabled, true),
				freq(0),
				lastEditSelectedUnits(5)
{
}


void Channel::select(bool setOn) {
	ind_selected.on(setOn);
}

void Channel::enable(bool setOn) {
	ind_enabled.on(setOn);
}

} /* namespace UI */
} /* namespace LOGuvnor */
