/*
 * UI.h
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

#ifndef UI_UI_H_
#define UI_UI_H_

#include "Display.h"
#include "Channel.h"
#include "Switch.h"

namespace LOGuvnor {
namespace UI {

class UI {
public:
	UI(ChannelConfig chanConfs[(uint8_t)Channel_BOUNDS],
	   SwitchConfig switchConfs[(uint8_t)Button_BOUNDS]);

	void begin();
	void tick();

	Display & display() { return _display;}
	Channel & channel(ChannelID cid);
	Switch & button(ButtonID swid);

	Indication & status() { return _status; }

	void setAllButtonCallbacks(Switch::ChangedCallback cb);


	bool haveSelectedChannel();
	Channel & selectedChannel();
	void clearSelectedChannel();
	uint8_t numChannelsEnabled();



private:
	Display _display;
	Channel _channels[(uint8_t)Channel_BOUNDS];
	Switch _switches[(uint8_t)Button_BOUNDS];
	Indication _status;



};

} /* namespace UI */
} /* namespace LOGuvnor */

#endif /* UI_UI_H_ */
