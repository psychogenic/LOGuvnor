/*
 * ChannelDetails.h, part of the LOGuvnor project
 *
 *  Created on: Nov 29, 2023
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
 *  See the full frequency and state.  Lets you choose which
 *  digit to edit and move to ChannelEdit or back to Summary.
 *
 */

#ifndef BEHAVIOUR_CHANNELDETAILS_H_
#define BEHAVIOUR_CHANNELDETAILS_H_

#include "Behaviour.h"

namespace LOGuvnor {
namespace Behaviour {

class ChannelDetails : public Behaviour {
public:
	ChannelDetails();
	virtual void load();
	virtual void refresh();

protected:
	/* action overrides */
	// twist knob to select frequency digit to edit, moving cursor
	virtual void knobPositionChange(RotEncoderPosition toPosition,
									RotEncoderPosition deltaFromLast);

	// select or knob press: edit the frequency
	// at currently specified digit
	virtual void selectAction();
	virtual void knobAction();

	// function press: get outta here, go back
	virtual void functionAction();

};

} /* namespace Behaviour */
} /* namespace LOGuvnor */

#endif /* BEHAVIOUR_CHANNELDETAILS_H_ */
