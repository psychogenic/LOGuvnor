/*
 * Summary.h, part of the LOGuvnor project
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
 *  Summary Behaviour: shows useful stats for all channels
 *  and lets you select one to focus on.
 *
 *  Will move you to ChannelDetails, on select on knob press
 *
 */

#ifndef BEHAVIOUR_SUMMARY_H_
#define BEHAVIOUR_SUMMARY_H_

#include "Behaviour.h"

namespace LOGuvnor {
namespace Behaviour {

class Summary : public Behaviour {
public:
	Summary();

	virtual void load();
	virtual void refresh();

protected:
	/* action overrides */

	// select or knob press: go to ChannelDetails
	// on currently highlighted channel
	virtual void selectAction();
	virtual void knobAction();

	// change highlight/selection according to delta
	virtual void knobPositionChange(RotEncoderPosition toPosition,
									RotEncoderPosition deltaFromLast);

	// knobless operation: advance highlight/select position by 1
	virtual void functionAction();
};

} /* namespace Behaviour */
} /* namespace LOGuvnor */

#endif /* BEHAVIOUR_SUMMARY_H_ */
