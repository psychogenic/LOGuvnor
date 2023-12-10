/*
 * Globals.cpp, part of the LOGuvnor project
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

#include "Globals.h"
#include "behaviour/SplashScreen.h"
#include "behaviour/Summary.h"
#include "behaviour/ChannelDetails.h"
#include "behaviour/ChannelEdit.h"

#define DYN_ALLOCATE_GLOBALS

namespace LOGuvnor {

uint8_t Globals::sel_units = 0;
uint8_t Globals::selectedUnits() {
	return sel_units;
}

void Globals::setSelectedUnits(uint8_t pos) {
	sel_units = pos;
}

Globals::Globals() {

}


UI::UI & Globals::ui() {

	LOGuvnor::UI::ChannelConfig glob_chanconf[3] = {
			{LOGuvnor::Channel_1, PIN_INDIC_nCHANSEL_1, PIN_INDIC_nCHANENA_1},
			{LOGuvnor::Channel_2, PIN_INDIC_nCHANSEL_2, PIN_INDIC_nCHANENA_2},
			{LOGuvnor::Channel_3, PIN_INDIC_nCHANSEL_3, PIN_INDIC_nCHANENA_3}
	};
	LOGuvnor::UI::SwitchConfig glob_swconf[4] = {
			{LOGuvnor::Button_ChannelEnable, PIN_SW_CHANEN, true},
			{LOGuvnor::Button_ChannelSelect, PIN_SW_CHANSEL, true},
			{LOGuvnor::Button_Function, PIN_SW_FUNCTION, true},
			{LOGuvnor::Button_RotaryEncoder, PIN_ROTSWITCH, false}, // TODO:CHECK

	};
#ifdef DYN_ALLOCATE_GLOBALS
	// static UI::UI _ui(glob_chanconf, glob_swconf);
	static UI::UI * _ui = NULL;
	if (! _ui)
	{
		_ui = new UI::UI(glob_chanconf, glob_swconf);
	}
	return *_ui;
#else
	static UI::UI _ui(glob_chanconf, glob_swconf);
	return _ui;
#endif

}
UI::Display & Globals::display() {
	return ui().display();
}

Driver & Globals::driver() {
#ifdef DYN_ALLOCATE_GLOBALS
	static Driver * d = NULL;
	if (! d) {
		d = new Driver(behaviour(Behaviour::Type::SplashScreen));
	}
	return *d;
#else
	static Driver d(behaviour(Behaviour::Type::SplashScreen));
	return d;
#endif
}
SignalGenerator & Globals::signalGenerator() {
#ifdef DYN_ALLOCATE_GLOBALS
	static SignalGenerator * _siggen;
	if (! _siggen) {
		_siggen = new SignalGenerator();
	}
	return *_siggen;
#else
	static SignalGenerator _siggen;

	return _siggen;
#endif
}


Behaviour::Behaviour * Globals::behaviour(Behaviour::Type::ID tp) {

#ifdef DYN_ALLOCATE_GLOBALS
	static Behaviour::Behaviour * allBev[] = {
			new Behaviour::SplashScreen(),
			new Behaviour::Summary(),
			new Behaviour::ChannelDetails(),
			new Behaviour::ChannelEdit(),
			NULL};
#else

	static Behaviour::SplashScreen _splash;
	static Behaviour::Summary _sum;
	static Behaviour::ChannelDetails _chanDeets;
	static Behaviour::ChannelEdit _chanEdit;
	static Behaviour::Behaviour * allBev[] = {
			&_splash,
			&_sum,
			&_chanDeets,
			&_chanEdit,
			NULL,
	};
#endif

	uint8_t i = 0;
	while (allBev[i]) {
		if (allBev[i]->id() == tp) {
			return allBev[i];
		}
		i++;
	}

	return NULL;


}




} /* namespace LOGuvnor */
