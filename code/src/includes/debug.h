/*
 * debug.h
 *
 *  Created on: Nov 26, 2023
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

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

#include "LOGuvnorConfig.h"

#ifdef DESKTOP_BUILD
#include <iostream>

#define DEBUG_OUT(...)  std::cerr << __VA_ARGS__
#define DEBUG_OUTLN(...)  std::cerr << __VA_ARGS__ << std::endl

#else


#ifdef DEBUG_SERIAL_BAUDRATE
#define DEBUG_OUT(...)  Serial.print(__VA_ARGS__)
#define DEBUG_OUTLN(...)  Serial.println(__VA_ARGS__)
#else

#define DEBUG_OUT(...)
#define DEBUG_OUTLN(...)

#endif
#endif



#endif /* SRC_DEBUG_H_ */
