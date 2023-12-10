/*
 * SignalGenerator.h, part of the LOGuvnor project
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
 *
 *  Simple interface to wrap whichever SI5351 library we wanna
 *  use.
 *
 *
 */

#ifndef SIGGEN_SIGNALGENERATOR_H_
#define SIGGEN_SIGNALGENERATOR_H_
#include "../includes/projectIncludes.h"

namespace LOGuvnor {

class SignalGenerator {
public:
	typedef struct Si5351Status DeviceStatus;
	typedef enum si5351_clock   DeviceClock;

	SignalGenerator();
	bool begin();

	bool ready() { return moduleFound;}


	const DeviceStatus & status(bool update=false);

	void enable(ChannelID cid, bool setEnabled=true);
	void disable(ChannelID cid) { enable(cid, false);}
	void disableAll();

	void setFrequency(ChannelID cid, FrequencyHz f);


private:
	DeviceClock channelToClock(ChannelID cid);


	bool moduleFound;
	Si5351 si5351;

};

} /* namespace LOGuvnor */

#endif /* SIGGEN_SIGNALGENERATOR_H_ */
