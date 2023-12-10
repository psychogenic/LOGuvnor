/*
 * Summary.cpp, part of the LOGuvnor project
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
 */

#include "behaviour/Summary.h"
#include "../Globals.h"

namespace LOGuvnor {
namespace Behaviour {

Summary::Summary() : Behaviour(Type::Summary) {

}

void Summary::load() {
	refresh();
}

void Summary::refresh() {

	Globals::display().showSummary();
}

void Summary::knobPositionChange(RotEncoderPosition toPosition,
		RotEncoderPosition deltaFromLast)
{
	incrementSelectedChannel(deltaFromLast);
	refresh();

}


void Summary::functionAction() {

	setPosition(position() + 1);
	knobPositionChange(position(), 1);
}



void Summary::selectAction() {
	if (Globals::ui().haveSelectedChannel()) {
			Globals::driver().scheduleBehaviourLoad(Type::DetailView);
	} else {
		functionAction();
	}
}
void Summary::knobAction() {

	selectAction();

}


} /* namespace Behaviour */
} /* namespace LOGuvnor */
