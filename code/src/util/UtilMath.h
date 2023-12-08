/*
 * UtilMath.h, part of the LOGuvnor project
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
 *
 *
 *  Simple math routines used internally.  Mostly used because
 *  pow() is floating point and deals badly with my big numbers...
 *  No 99999 is not the same as 100000, ugh.
 *
 */

#ifndef UTIL_UTILMATH_H_
#define UTIL_UTILMATH_H_
#include "../includes/projectIncludes.h"

namespace LOGuvnor {
namespace Util {

class Math {
public:
	static uint32_t pow10(uint8_t i);
	static uint32_t digitValue(uint8_t val, uint8_t tenpow);

private:
	// just use the static methods, no instances required
	Math();
};

} /* namespace Util */
} /* namespace LOGuvnor */

#endif /* UTIL_UTILMATH_H_ */
