/*
 * ChannelDetails.cpp, part of the LOGuvnor project
 *
 *  Created on: Nov 29, 2023
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

#include "behaviour/ChannelDetails.h"
#include "../Globals.h"

namespace LOGuvnor {
namespace Behaviour {

ChannelDetails::ChannelDetails() :  Behaviour(Type::DetailView) {
}

void ChannelDetails::load() {

	if (Globals::ui().haveSelectedChannel()) {
		Globals::setSelectedUnits(Globals::ui().selectedChannel().editingSelectedUnits());
	}
	refresh();
}

void ChannelDetails::refresh() {
	if (! Globals::ui().haveSelectedChannel()) {
		flashError(F("No sel?"));
		Globals::driver().scheduleBehaviourLoad(Type::Summary);
	}

	Globals::display().showChannel(Globals::ui().selectedChannel(),
			Globals::selectedUnits(), true);
}



void ChannelDetails::functionAction() {
	Globals::driver().scheduleBehaviourLoad(Type::Summary);
}

void ChannelDetails::selectAction() {
	Globals::driver().scheduleBehaviourLoad(Type::DetailEdit);
}
void ChannelDetails::knobAction() {
	Globals::driver().scheduleBehaviourLoad(Type::DetailEdit);
}

void ChannelDetails::knobPositionChange(RotEncoderPosition toPosition,
		RotEncoderPosition deltaFromLast)
{
	int8_t delta = deltaFromLast % NUMDIGITS_MAX;

#ifdef FREQEDIT_DIGITSELECTKNOB_INVERT
	int8_t newVal = Globals::selectedUnits() - delta;
#else
	int8_t newVal = Globals::selectedUnits() + delta;
#endif

	if (newVal < 0) {
		newVal += NUMDIGITS_MAX;
	}
	newVal = newVal % NUMDIGITS_MAX;

	Globals::setSelectedUnits(newVal);
	Globals::ui().selectedChannel().setEditingSelectedUnits(newVal);

	refresh();
}

} /* namespace Behaviour */
} /* namespace LOGuvnor */
