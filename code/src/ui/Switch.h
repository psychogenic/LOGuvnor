/*
 * Switch.h
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
 * MOM switches are used as the buttons in the system.
 *
 * The platform has a limited number of true interrupt
 * capable pins, so these are basically polled (on tick())
 * and, when a state change is noticed the callback
 * is triggered if set.
 *
 */

#ifndef UI_SWITCH_H_
#define UI_SWITCH_H_

#include "../includes/projectIncludes.h"
namespace LOGuvnor {
namespace UI {

// struct to make for easy looping
// in c'tor calls
typedef struct switchconfstr {
	ButtonID id;
	Pin monitoredPin;
	bool inverted;
} SwitchConfig;

class Switch {
public:
	typedef void(*ChangedCallback)(ButtonID sw, bool state);
	Switch(ButtonID sw, Pin monitoredPin, bool inverted=false, ChangedCallback cb=NULL);
	Switch(const SwitchConfig & conf);

	void tick(); // poll

	ButtonID id();
	bool state() ;

	ChangedCallback callback();
	void setCallback(ChangedCallback cb);

private:
	ButtonID _id;
	bool _state;
	ChangedCallback _callback;
	Pin pin;
	bool invert;
};

} /* namespace UI */
} /* namespace LOGuvnor */

#endif /* UI_SWITCH_H_ */
