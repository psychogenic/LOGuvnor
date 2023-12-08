/*
 * Driver.h, part of the LOGuvnor project
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
 *
 *  The driver is the public facing part of the system,
 *  that maps UI and behavioral elements to each other.
 *  It allows behaviours to move between themselves
 *  with minimal coupling, accepts events about position (rot-enc
 *  knob) and basically keeps everyone ticking/alive.
 *
 *
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "ui/UI.h"
#include "behaviour/Behaviour.h"

namespace LOGuvnor {

class Driver {
public:
	Driver(Behaviour::Behaviour * startupBehaviour);
	// lifecycle
	void begin();
	void tick();

	// major elements
	UI::UI & ui();
	Behaviour::Behaviour * behaviour() { return currentBehaviour;}
	Behaviour::Type::ID mode() { return currentBehaviour->id(); }

	// outside event notifs
	void positionChangeEvent(RotEncoderPosition currentPosition);
	void buttonInterrupt(ButtonID swid, bool state);

	// used by behaviours:
	void scheduleBehaviourLoad(Behaviour::Type::ID tp);
private:
	Behaviour::Behaviour * currentBehaviour;
	Behaviour::Type::ID nextBehaviour;
};

} /* namespace LOGuvnor */

#endif /* DRIVER_H_ */
