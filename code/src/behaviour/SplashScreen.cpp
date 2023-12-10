/*
 * SplashScreen.cpp, part of the LOGuvnor project
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

#include "behaviour/SplashScreen.h"
#include "util/utils.h"
#include "Globals.h"
namespace LOGuvnor {
namespace Behaviour {

SplashScreen::SplashScreen() : Behaviour(Type::SplashScreen), delay_count(0) {

}

void SplashScreen::load() {
	delay_count = 0;
	/*
	for (uint8_t i=0; i<10; i++) {

		Globals::display().clear();
		Globals::display().debugMessage(i);
		Globals::display().debugMessage(F(": "));
		Globals::display().debugMessage(Util::Math::digitValue(1, i));

		Globals::display().flush();
		delay(1000);

	}
	*/


	Globals::display().showSplash();

}

void SplashScreen::unload() {
}

void SplashScreen::tick() {

	if (delay_count) {
		Globals::driver().scheduleBehaviourLoad(Type::Summary);
		return;
	}
	if (Globals::signalGenerator().ready()) {

		Globals::display().debugMessage(F("Si5351:"));
	} else {
		flashError(F("No siggen?\nSi5351 not found!"));

		//Globals::display().clear();
		Globals::display().debugMessage(F("ERR:"));

		Globals::display().debugMessage((uint32_t)Globals::signalGenerator().status().LOL_A);
		Globals::display().debugMessage((uint32_t)Globals::signalGenerator().status().LOL_B);

	}


	Globals::display().debugMessage((uint32_t)Globals::signalGenerator().status(true).SYS_INIT);
	Globals::display().debugMessage((uint32_t)Globals::signalGenerator().status().REVID);
	Globals::display().flush();
	DELAY_MS(500);

	delay_count ++;
}

} /* namespace Behaviour */
} /* namespace LOGuvnor */
