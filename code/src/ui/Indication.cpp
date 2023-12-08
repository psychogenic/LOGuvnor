/*
 * Indication.cpp
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

#include "ui/Indication.h"

namespace LOGuvnor {
namespace UI {

Indication::Indication(Pin p, bool inverted) :
		pin(p), invert(inverted), _state(false)
{
}

void Indication::on(bool setOn) {
	_state = setOn; // save the actual logical state

	// may need to flip pin, depending on wiring
	bool setAs = invert ? !_state : _state;
	if (setAs) {
		DIGITALWRITE_HIGH(pin);
	} else {
		DIGITALWRITE_LOW(pin);
	}
}


bool Indication::state() {
	return _state;
}


void Indication::off() {
	on(false);
}


} /* namespace UI */
} /* namespace LOGuvnor */
