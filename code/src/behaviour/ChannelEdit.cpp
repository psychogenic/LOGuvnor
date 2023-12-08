/*
 * ChannelEdit.cpp, part of the LOGuvnor project
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

#include "ChannelEdit.h"
#include "../Globals.h"
#include "../util/utils.h"

namespace LOGuvnor {
namespace Behaviour {

ChannelEdit::ChannelEdit() : Behaviour(Type::DetailEdit) {

}

void ChannelEdit::load() {
	refresh();
}

void ChannelEdit::refresh() {
	Globals::display().showChannel(Globals::ui().selectedChannel(),
			Globals::selectedUnits(), true, true);
}


void ChannelEdit::setEditedFrequency(FrequencyHz freq) {
	UI::Channel & ch = Globals::ui().selectedChannel();
	if (freq < FREQUENCY_MINIMUM_HZ) {
			freq = FREQUENCY_MINIMUM_HZ;
	}
	ch.setFrequency(freq);
	Globals::signalGenerator().setFrequency(ch.id(), freq);

}
void ChannelEdit::selectAction() {

	Globals::driver().scheduleBehaviourLoad(Type::DetailView);

}



void ChannelEdit::functionAction() {

	uint32_t scale = 1;
	if (Globals::selectedUnits() != SELECTED_UNITS_NA) {
		FrequencyHz freq = Globals::ui().selectedChannel().frequency().value();
		scale = Util::Math::pow10(Globals::selectedUnits());
		FrequencyHz toRemove = freq % scale;
		freq -= toRemove;
		if (freq >= FREQUENCY_MINIMUM_HZ )
		{
			setEditedFrequency(freq);
			refresh();
		}

	} else {
		setPosition(position() + 1);
		knobPositionChange(position(), 1);
	}
}

void ChannelEdit::knobAction() {
	Globals::driver().scheduleBehaviourLoad(Type::DetailView);

}

void ChannelEdit::knobPositionChange(RotEncoderPosition toPosition,
		RotEncoderPosition deltaFromLast) {

	int32_t valueAdded = 0;
	uint32_t scale = 1;
	FrequencyHz freq = Globals::ui().selectedChannel().frequency().value();
	if (Globals::selectedUnits() == SELECTED_UNITS_NA) {
		Globals::setSelectedUnits(2);
	}

	if (Globals::selectedUnits()) {
		scale = Util::Math::pow10(Globals::selectedUnits());
	} else {
		scale = 1;
	}

	valueAdded = deltaFromLast * scale;
	freq = freq + valueAdded;
	if ((int32_t)freq + valueAdded < FREQUENCY_MINIMUM_HZ) {
		freq = FREQUENCY_MINIMUM_HZ;
	} else if (freq > FREQUENCY_MAXIMUM_HZ) {
		freq = FREQUENCY_MAXIMUM_HZ;
	}


	setEditedFrequency(freq);

	refresh();
}

} /* namespace Behaviour */
} /* namespace LOGuvnor */
