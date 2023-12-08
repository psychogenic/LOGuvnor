/*
 * SignalGenerator.cpp, part of the LOGuvnor project
 *
 *  Created on: Nov 30, 2023
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

#include "SignalGenerator.h"
#include "../includes/LOGuvnorConfig.h"

namespace LOGuvnor {

SignalGenerator::SignalGenerator() : moduleFound(false)
{

}


const SignalGenerator::DeviceStatus & SignalGenerator::status(bool update) {
	if (update) {
		si5351.update_status();
	}
	return si5351.dev_status;
}

bool SignalGenerator::begin() {

	  moduleFound = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, SI5351_CORRECTIONFACTOR);
	  if (moduleFound) {
		  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVESTRENGTH);
	  }
	  return moduleFound;
}

void SignalGenerator::setFrequency(ChannelID cid, FrequencyHz f) {
	si5351.set_freq(f * SI5351_FREQ_MULT, channelToClock(cid));

}

void SignalGenerator::enable(ChannelID cid, bool setEnabled) {
	uint8_t en=0;
	if (setEnabled) {
		en = 1;
	}
	si5351.output_enable(channelToClock(cid), en);
}

void SignalGenerator::disableAll() {
	enable(Channel_1, false);
	enable(Channel_2, false);
	enable(Channel_3, false);


}

SignalGenerator::DeviceClock SignalGenerator::channelToClock(ChannelID cid) {

	switch (cid) {
	case Channel_1:
		return SI5351_CLK0;
	case Channel_2:
		return SI5351_CLK1;
	default:
		return SI5351_CLK2;

	}
}

} /* namespace LOGuvnor */
