/*
 * Behaviour.cpp, part of the LOGuvnor project
 *
 *  Created on: Nov 28, 2023
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

#include "Behaviour.h"
#include "../Globals.h"

namespace LOGuvnor {
namespace Behaviour {

// share same currentPosition between all
// behaviours, so we don't suddenly freakout
// when a small step happens after we've been
// loaded (if each behav keeps it's own marker
// it takes more room and goes stale while another
// is loaded and seeing movement)
RotEncoderPosition Behaviour::currentPosition;
uint16_t Behaviour::tick_count = 0;
Behaviour::Behaviour(Type::ID behaveType) : _behavId(behaveType)
{

}
void Behaviour::buttonChangeEvent(ButtonID swid, bool state) {
	if (! state) {
		return; // only care when activated, release is meh
	}

	// call appropriate action
	switch (swid) {
		case Button_ChannelEnable:
				this->enableAction();
				break;
		case Button_ChannelSelect:
				this->selectAction();
				break;
		case Button_Function:
				this->functionAction();
				break;
		case Button_RotaryEncoder:
				this->knobAction();
				break;
		default:
			/* can't happen */
			break;
	}

}

void Behaviour::knobChangeEvent(RotEncoderPosition toPosition) {
	RotEncoderPosition delta = toPosition - currentPosition;

	// only trigger if we've actually moved
	if (delta != 0) {
		currentPosition = toPosition;
		// yep: call instance handler
		this->knobPositionChange(toPosition, delta);
	}
}

/* default "enable" button action:
 * enable the selected channel.
 */
void Behaviour::enableAction() {
	if (! Globals::ui().haveSelectedChannel())
	{
		flashErrorSelectChannel();
		return;
	}
	UI::Channel & ch = Globals::ui().selectedChannel();

	ch.enable(! ch.enabled() ); // toggle enable
	// tell the sig gen
	Globals::signalGenerator().enable(ch.id(), ch.enabled());

	refresh();
}


void Behaviour::load() {
	Globals::ui().display().clear();
}
void Behaviour::tick() {
	tick_count++;
}
void Behaviour::flashError(ERR_MSG_STR errmsg) {

	Globals::display().showError(errmsg);
	DELAY_MS(ERROR_MESSAGEFLASH_MS/3);
	Globals::display().clear();
	DELAY_MS(ERROR_MESSAGEFLASH_MS/3);
	Globals::display().showError(errmsg);
	DELAY_MS(ERROR_MESSAGEFLASH_MS/3);

	this->refresh();
}


void Behaviour::flashErrorSelectChannel() {
	flashError(F("Select Channel"));
}


bool Behaviour::buttonState(ButtonID bid) {
	return Globals::ui().button(bid).state();
}

void Behaviour::incrementSelectedChannel(RotEncoderPosition byAmount) {

	ChannelID selChan = Channel_BOUNDS;
	if (! Globals::ui().haveSelectedChannel()) {
		// first time around, select first channel
		Globals::ui().channel(Channel_1).select();
		return;
	}
	selChan = Globals::ui().selectedChannel().id();
	bool reverse = false;
	if (byAmount < 0) {
		reverse = true;
		byAmount = -1 * byAmount;
	}

	int8_t selChange = byAmount % (uint8_t)Channel_BOUNDS;

	if (reverse) {
		selChange = -1 * selChange;
	}
	int8_t newChan = ((uint8_t)selChan + selChange);
	if (newChan >= (uint8_t)Channel_BOUNDS) {
		newChan = newChan % (uint8_t)Channel_BOUNDS;
	}
	while (newChan < 0) {
		newChan = (uint8_t)Channel_BOUNDS + newChan;
	}
	Globals::ui().clearSelectedChannel();
	Globals::ui().channel((ChannelID)newChan).select();
}

} /* namespace Behaviour */
} /* namespace LOGuvnor */
