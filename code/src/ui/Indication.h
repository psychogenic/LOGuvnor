/*
 * Indication.h
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
 *
 * An indication LED, tied to a specific
 * pin, is either set on or not, maintains that
 * state and can handle inverted logic pins.
 *
 * Though these are UI elements, to save on
 * space/processing the act as both View and
 * Model in that they are where the particular
 * flag/state is stored system wide.
 *
 * In this way, they act similar to the channel,
 * holding state in a UI element, pretty much
 * breaking MVC for simplicity's sake.
 *
 */
#ifndef UI_INDICATION_H_
#define UI_INDICATION_H_

#include "../includes/projectIncludes.h"

namespace LOGuvnor {
namespace UI {

class Indication {
public:
	Indication(Pin p, bool inverted = false);


	void on(bool setOn = true);
	void off();
	void toggle() { on(!state()); } // just flip it

	bool state();
private:
	Pin pin;
	bool invert;
	bool _state;
};

} /* namespace UI */
} /* namespace LOGuvnor */

#endif /* UI_INDICATION_H_ */
