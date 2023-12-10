/*
 * Globals.h, part of the LOGuvnor project
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
 *
 *  Globals: a clean way to give all the bits that play
 *  with each other access to each other.
 *
 *  Everything here is a singleton, though that is just
 *  enforced by convention and the fact that the system
 *  uses calls to Globals::staticMethod() to access them.
 *
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_
#include "ui/UI.h"
#include "Driver.h"
#include "behaviour/Behaviour.h"
#include "siggen/SignalGenerator.h"

namespace LOGuvnor {

class Globals {
public:
	// the main driver/public interface
	static Driver & driver();

	// the main gateway to the UI
	static UI::UI & ui();

	// the signal generator we're controlling
	// with everything else
	static SignalGenerator & signalGenerator();

	// shorthand for ui().display()
	static UI::Display & display();

	// Behaviour by type accessor
	static Behaviour::Behaviour * behaviour(Behaviour::Type::ID tp);

	// the selected "units" (i.e. the specific frequency
	// digit being edited), storing here to preserve state
	// over time and channel for various modes
	static uint8_t selectedUnits();
	static void setSelectedUnits(uint8_t pos);

private:
	static uint8_t sel_units;

	// just use the static methods, no instances required
	Globals();
};

} /* namespace LOGuvnor */

#endif /* GLOBALS_H_ */
