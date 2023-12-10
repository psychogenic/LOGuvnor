/*
 * UtilMath.cpp, part of the LOGuvnor project
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
 */

#include "util/UtilMath.h"

namespace LOGuvnor {
namespace Util {

uint32_t Math::pow10(uint8_t i) {
	static uint32_t vals[NUMDIGITS_MAX] = {
			1,
			10,
			100,
			1000,
			10000,
			100000ULL,
			1000000ULL,
			10000000ULL,
			100000000ULL,
	};

	if (i >= NUMDIGITS_MAX) {
		return 0;
	}
	return vals[i];
}

uint32_t Math::digitValue(uint8_t val, uint8_t tenpow) {
	if (val >= NUMDIGITS_MAX) {
		return 0;
	}
	return pow10(tenpow) * (uint32_t)val;
}

Math::Math() {

}

} /* namespace Util */
} /* namespace LOGuvnor */
