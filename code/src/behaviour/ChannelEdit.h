/*
 * ChannelEdit.h, part of the LOGuvnor project
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
 *  Modify the frequency (or enable/disable state of course).
 *  Dead-end: move back to ChannelDetails from here.
 *
 *  Function key, while editing frequency, will zero all
 *  digits smaller than selected.
 *
 */

#ifndef BEHAVIOUR_CHANNELEDIT_H_
#define BEHAVIOUR_CHANNELEDIT_H_

#include "Behaviour.h"

namespace LOGuvnor {
namespace Behaviour {

class ChannelEdit : public Behaviour {
public:
	ChannelEdit();
	virtual void load();
	virtual void refresh();
	// virtual void unload();

protected:
	/* action overrides */

	// select or knob press: go back to channel deets
	virtual void selectAction();
	virtual void knobAction();

	// increase/decrease freq by selected-units increments
	virtual void knobPositionChange(RotEncoderPosition toPosition,
									RotEncoderPosition deltaFromLast);

	// zeros everything after the selected digit, if possible.
	virtual void functionAction();

private:
	void setEditedFrequency(FrequencyHz freq);

};

} /* namespace Behaviour */
} /* namespace LOGuvnor */

#endif /* BEHAVIOUR_CHANNELEDIT_H_ */
