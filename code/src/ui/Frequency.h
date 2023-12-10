/*
 * Frequency.h, part of the LOGuvnor project
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
 * Wrapper class for target frequencies, in Hz.
 * Holds the actual value, and also breaks it down
 * into individual digits and holds on to the "range"
 * scale (e.g. kiloHz, tens of kHz, etc) for quicker
 * processing during display.
 *
 */

#ifndef UI_FREQUENCY_H_
#define UI_FREQUENCY_H_

#include "../includes/LOGuvnorTypes.h"

namespace LOGuvnor {
namespace UI {


class Frequency {
public:
	typedef enum {
		Kilo = 3,
		TenKilo = 4,
		HundredKilo = 5,
		Mega = 6,
		TenMega = 7,
		HundredMega = 8
	} Scale;
	// c'tor
	Frequency(uint32_t val=FREQUENCY_MINIMUM_HZ);

	Scale scale() const { return _scale;}

	void setValue(uint32_t val);
	FrequencyHz value() const { return _value;}

	const uint8_t * digits() const { return _digits;}
	uint8_t digit(uint8_t idx) const { return _digits[idx];}
	inline uint8_t numDigits() const { return NUMDIGITS_MAX;}


private:
	void parse();
	FrequencyHz _value;
	Scale _scale;
	uint8_t _digits[NUMDIGITS_MAX];
	uint8_t _selected_digit;
};

} /* namespace UI */
} /* namespace LOGuvnor */

#endif /* UI_FREQUENCY_H_ */
