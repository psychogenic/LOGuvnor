/*
 * Driver.cpp, part of the LOGuvnor project
 *
 *  Created on: Nov 27, 2023
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

#include "Driver.h"
#include "Globals.h"

// global scope callback for detected button state changes
void driverButtonStatechangeCallback(LOGuvnor::ButtonID swid, bool state) {
	LOGuvnor::Globals::driver().buttonInterrupt(swid, state);
}

namespace LOGuvnor {


Driver::Driver(Behaviour::Behaviour * startupBehaviour) : currentBehaviour(startupBehaviour),
		nextBehaviour(Behaviour::Type::Type_BOUNDS)
{
}
void Driver::buttonInterrupt(ButtonID swid, bool state) {
	// pass it on to current behaviour
	LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(swid, state);
}


void Driver::positionChangeEvent(RotEncoderPosition currentPosition)
{
	// pass that on to current behaviour
	currentBehaviour->knobChangeEvent(currentPosition);
}

UI::UI & Driver::ui() {
	return Globals::ui();
}

void Driver::scheduleBehaviourLoad(Behaviour::Type::ID tp) {
	nextBehaviour = tp;
}

void Driver::begin() {
	// startup UI and make the buttons tell me when
	// something changes
	ui().begin();
	ui().status().on(true);
	ui().setAllButtonCallbacks(driverButtonStatechangeCallback);

	// first behaviour, load her up
	currentBehaviour->load();

	if (Globals::signalGenerator().begin()) {
		// sig-gen is good, set it up with default
		// frequencies, but ensure all are disabled
		for (uint8_t cid=0; cid<(uint8_t)Channel_BOUNDS; cid++) {
			Globals::signalGenerator().setFrequency((ChannelID)cid,
					Globals::ui().channel((ChannelID)cid).frequency().value());
		}
		Globals::signalGenerator().disableAll();
	} else {
		#ifdef DIE_ON_SIGGEN_ERROR
		for (;;) {

			DEBUG_OUTLN(F("Could not start siggen??"));
			ui().status().toggle();
			DELAY_MS(100);

		}
		#endif
	}

	ui().status().on(STATUS_LED_ON_DURING_OPERATION);
}

void Driver::tick() {
	// on each tick, tick UI and behaviour
	ui().tick();
	currentBehaviour->tick();
	// if we've got a request to load up a new behaviour,
	// do that
	if (nextBehaviour != Behaviour::Type::Type_BOUNDS) {
		Behaviour::Behaviour * nextBehav = Globals::behaviour(nextBehaviour);
		nextBehaviour = Behaviour::Type::Type_BOUNDS;
		if (! nextBehav ) {
			currentBehaviour->flashError(F("NO BHV"));
			return;
		}
		currentBehaviour->unload(); // unload the first
		// assign new current, and load up
		currentBehaviour = nextBehav;
		currentBehaviour->load();
	} else {

		if (STATUS_LED_ON_DURING_OPERATION
				&&
				currentBehaviour->tickCount() % STATUS_LED_HEARTBEAT_TICKPERIOD == 0) {
			ui().status().toggle();
		}

	}
}

} /* namespace LOGuvnor */
