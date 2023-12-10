/*
 * Channel.h
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
 * A channel is one of the clocks we can use (there
 * are 3).
 *
 * It's a higher-level UI element, meant to associate:
 *
 *   - the selection indicator
 *   - the enabled indicator
 *   - the frequency it's currently set to
 *
 * Though this is a part of the UI, it's not pure
 * "view" (in the MVC sense), in that I want to save
 * some space, so this is the one-true-place where
 * the frequency value is stored... so, it's not only
 * view, it's also acting as Model. (The indicators
 * work similarly, where the selected/enabled state
 * is shown by these UI elements, but also that's
 * where they're stored.)
 *
 * The frequency attribute isn't just a plain number,
 * it's a Frequency object, which does some processing
 * for us to make displaying and editing easier.
 *
 *
 */

#ifndef UI_CHANNEL_H_
#define UI_CHANNEL_H_

#include "../includes/projectIncludes.h"
#include "Indication.h"
#include "Frequency.h"


namespace LOGuvnor {
namespace UI {

// struct to make for easy looping
// in c'tor calls
typedef struct {
	ChannelID cid;
	Pin indicateSelect;
	Pin indicateEnabled;
} ChannelConfig;

class Channel {
public:
	Channel(ChannelID cid, Pin indicateSelect, Pin indicateEnabled);
	Channel(const ChannelConfig & conf);

	ChannelID id() { return channelid;}

	bool selected() { return ind_selected.state();}
	bool enabled() { return ind_enabled.state();}

	void select(bool setOn=true);
	void deselect() { select(false);}
	void enable(bool setOn=true);
	void disable() { enable(false); }

	const Frequency & frequency() { return freq;}
	void setFrequency(FrequencyHz f) { freq.setValue(f);}

	uint8_t editingSelectedUnits() { return lastEditSelectedUnits;}
	void setEditingSelectedUnits(uint8_t su) { lastEditSelectedUnits = su;}

private:
	ChannelID channelid;
	Indication ind_selected;
	Indication ind_enabled;
	Frequency freq;
	uint8_t lastEditSelectedUnits;

};

} /* namespace UI */
} /* namespace LOGuvnor */

#endif /* UI_CHANNEL_H_ */
