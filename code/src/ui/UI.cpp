/*
 * UI.cpp
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

#include "UI.h"
#include "../Globals.h"

namespace LOGuvnor {
namespace UI {

UI::UI(ChannelConfig chanConfs[(uint8_t)Channel_BOUNDS],
		SwitchConfig switchConfs[(uint8_t)Button_BOUNDS]) :
		_display(),
		_channels {
					Channel(chanConfs[0]),
					Channel(chanConfs[1]),
					Channel(chanConfs[2])},
		_switches {
					Switch(switchConfs[0]),
					Switch(switchConfs[1]),
					Switch(switchConfs[2]),
					Switch(switchConfs[3])
				},
		_status(PIN_STATUS, true)

{

	_display.setChannels(_channels);
}


void UI::begin() {

	FrequencyHz initFreq[] = {
			FREQUENCY_DEFAULT_CHANNEL_1,
			FREQUENCY_DEFAULT_CHANNEL_2,
			FREQUENCY_DEFAULT_CHANNEL_3
	};

	// status indicator, show's we're alive
	_status.off(); // start off

	for (uint8_t i=0; i<(uint8_t)Channel_BOUNDS; i++) {
		Channel & ch =channel((ChannelID)i);
		ch.setFrequency(initFreq[i]);
		ch.enable(false);
		ch.select(false);
		_status.toggle();
	}
#ifdef BEGIN_WITH_CHANNEL1_SELECTED
	channel(Channel_1).select();
#endif
	_display.begin();
	DEBUG_OUTLN("UI::begin done");
}
void UI::tick() {
	// tick all who need it
	for (uint8_t i=0; i<(uint8_t)Button_BOUNDS; i++) {
		_switches[i].tick();
	}

	_display.tick();
}

bool UI::haveSelectedChannel() {
	for (uint8_t i=0; i<(uint8_t)Channel_BOUNDS; i++) {
		if (_channels[i].selected()) {
			return true;
		}
	}
	return false;
}
Channel & UI::selectedChannel() {
	for (uint8_t i=0; i<(uint8_t)Channel_BOUNDS; i++) {
		if (_channels[i].selected()) {
			return _channels[i];
		}
	}
	return _channels[0];
}
uint8_t UI::numChannelsEnabled() {
	uint8_t num = 0;
	for (uint8_t i=0; i<(uint8_t)Channel_BOUNDS; i++) {
		if (_channels[i].enabled()) {
			num++;
		}
	}
	return num;
}
void UI::clearSelectedChannel() {

	for (uint8_t i=0; i<(uint8_t)Channel_BOUNDS; i++) {
		_channels[i].deselect();
	}
}

Channel& UI::channel(ChannelID cid) {
	if ((uint8_t)cid >= (uint8_t)Channel_BOUNDS) {
		cid = Channel_1;
	}
	return _channels[(uint8_t)cid];
}

Switch & UI::button(ButtonID swid) {
	if ((uint8_t)swid >= (uint8_t)Button_BOUNDS) {
		swid = Button_ChannelEnable;
	}
	return _switches[(uint8_t)swid];
}
void UI::setAllButtonCallbacks(Switch::ChangedCallback cb) {
	for (uint8_t swid = 0; swid <= (uint8_t)Button_BOUNDS; swid++) {
		_switches[swid].setCallback(cb);
	}
}

} /* namespace UI */
} /* namespace LOGuvnor */
