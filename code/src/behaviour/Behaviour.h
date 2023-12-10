/*
 * Behaviour.h, part of the LOGuvnor project
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
 *  The various modes of operation all use the same events
 *  (buttons/knobs) in different ways.
 *
 *  This is handled by the magic of polymorphism with
 *  mode-specific derivatives of Behaviour.
 *
 */

#ifndef BEHAVIOUR_BEHAVIOUR_H_
#define BEHAVIOUR_BEHAVIOUR_H_

#include "../includes/LOGuvnorTypes.h"
#include "../ui/Channel.h"

namespace LOGuvnor {
namespace Behaviour {

class Behaviour {
public:
	Behaviour(Type::ID behaveType);
	// virtual ~Behaviour() {} // no destructing will happen here, and it costs us bytes

	/* lifecycle */
	virtual void load();		// are coming into behaviour
	virtual void refresh() {} 	// refresh the screen
	virtual void unload() {}	// are leaving behaviour
	virtual void tick();		// life tick


	/* external world events */
	// these are triggered by driver as appropriate,
	// not meant for override: these message the relevant
	// (protected) handlers, below
	void buttonChangeEvent(ButtonID swid, bool state);
	void knobChangeEvent(RotEncoderPosition toPosition);


	Type::ID id() { return _behavId;}
	RotEncoderPosition position() { return currentPosition;}

	void flashError(ERR_MSG_STR errmsg);
	static uint16_t tickCount() { return tick_count;}

protected:
	/* these are for subclasses, event handlers and utilities */

	/* Event handlers -- override as required to do
	 * your specific mode thing
	 */
	virtual void enableAction(); /* implements default behav: i.e. just toggle enable */

	// other events are meant to be overridden
	// button trigger events
	virtual void selectAction() {}
	virtual void functionAction() {}
	virtual void knobAction() {}

	// rotary encoder change of position
	virtual void knobPositionChange(RotEncoderPosition toPosition,
			RotEncoderPosition deltaFromLast) {}


	/* utilities */
	void flashErrorSelectChannel();
	void incrementSelectedChannel(RotEncoderPosition byAmount);
	bool buttonState(ButtonID bid);
	void setPosition(RotEncoderPosition pos) { currentPosition = pos;}

	// if you want to play with it, a tick count
	// incremented on each tick by default
	static uint16_t tick_count;
private:
	Type::ID _behavId;
	static RotEncoderPosition currentPosition; // static to share, so we don't bounce around
};

} /* namespace Behaviour */
} /* namespace LOGuvnor */

#endif /* BEHAVIOUR_BEHAVIOUR_H_ */
