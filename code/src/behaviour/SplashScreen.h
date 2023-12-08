/*
 * SplashScreen.h, part of the LOGuvnor project
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
 *  Oh-so-splashy splash screen
 *
 */

#ifndef BEHAVIOUR_SPLASHSCREEN_H_
#define BEHAVIOUR_SPLASHSCREEN_H_

#include "Behaviour.h"

namespace LOGuvnor {
namespace Behaviour {

class SplashScreen : public Behaviour {
public:
	SplashScreen();

	// does basically nothing but load next stage, Summary
	virtual void load();
	// virtual void refresh();
	virtual void unload();
	virtual void tick();

private:
	uint8_t delay_count;

};

} /* namespace Behaviour */
} /* namespace LOGuvnor */

#endif /* BEHAVIOUR_SPLASHSCREEN_H_ */
