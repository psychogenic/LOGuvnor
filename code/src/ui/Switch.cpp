/*
 * Switch.cpp
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

#include "Switch.h"

namespace LOGuvnor {
namespace UI {

Switch::Switch(ButtonID sw, Pin monitoredPin, bool inverted, ChangedCallback cb) :
	_id(sw),
	_state(false),
	_callback(cb),
	pin(monitoredPin),
	invert(inverted)
{

}
Switch::Switch(const SwitchConfig & conf) :
			_id(conf.id),
			_state(false),
			_callback(NULL),
			pin(conf.monitoredPin),
			invert(conf.inverted)
{

}

ButtonID Switch::id() { return _id;}
bool Switch::state() { return _state;}

Switch::ChangedCallback Switch::callback() {return _callback;}
void Switch::setCallback(Switch::ChangedCallback cb) { _callback = cb;}

void Switch::tick() {
	bool triggerCallback = false;
	bool newState = DIGITALREAD(pin);
	// may need to flip, depending on pin wiring
	if (invert) {
		newState = !newState;
	}

	// check if we need to trigger prior to setting
	// internal state, so that if can go to callback and
	// the state we pass and our state() report will concord
	if (newState != _state) {
		triggerCallback = true;
	}
	// can now safely dump the last state
	// and store current
	_state = newState;

	if (triggerCallback && _callback) {
		DEBUG_OUT("Callback triggered for switch ");
		DEBUG_OUTLN((int)_id);
		_callback(_id, newState);
	}

}

} /* namespace UI */
} /* namespace LOGuvnor */

