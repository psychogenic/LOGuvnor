/*
 * Frequency.cpp, part of the LOGuvnor project
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

#include "Frequency.h"

namespace LOGuvnor {
namespace UI {

Frequency::Frequency(uint32_t val) : _value(val), _scale(Kilo), _selected_digit(NUMDIGITS_MAX - 1)
{

	parse();

}
void Frequency::setValue(uint32_t val)
{
	_value = val;
	parse();
}

void Frequency::parse() {

	FrequencyHz val = _value;
	FrequencyHz div = 10;
	FrequencyHz prevDiv = 1;

	// figure out the scale
	if (val >= 100000000ULL) {
		_scale = HundredMega;
	} else if (val >= 10000000ULL) {
		_scale = TenMega;
	} else if (val >= 1000000ULL) {
		_scale = Mega;
	} else if (val >= 100000ULL) {
		_scale = HundredKilo;
	} else if (val >= 10000UL) {
		_scale = TenKilo;
	} else {
		_scale = Kilo;
	}


	// reset everything to 0
	// don't want to use memset, go manual
	for (uint8_t i=0; i<NUMDIGITS_MAX; i++) {
		_digits[i] = 0;
	}

	// break into digits, basically by
	// breaking into the "10s" above and preserving
	// the remainder units in the appropriate slots
	// e.g.
	// 1234
	// digits[8] = (1234 % 10) / 1 == 4
	// 1234 - 4 = 1230
	// digits[7] = 1230 % 100 / 10 == 30 / 10 == 3
	// 1230 - 30 = 1200 ... etc
	for (int8_t i=NUMDIGITS_MAX - 1; i>=0; i--) {

		_digits[i] = (val % div)/prevDiv;
		val -= (_digits[i] * prevDiv);
		prevDiv = div;
		div *= 10;
		if (val == 0) {
			return;
		}
	}



}

} /* namespace UI */
} /* namespace LOGuvnor */
