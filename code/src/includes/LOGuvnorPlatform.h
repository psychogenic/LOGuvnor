/*
 * LOGuvnorPlatform.h
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

#ifndef LOGUVNORPLATFORM_H_
#define LOGUVNORPLATFORM_H_

#include <Arduino.h>

#define DIGITALWRITE(pin, val)	digitalWrite(pin, val)
#define DIGITALWRITE_HIGH(pin)	DIGITALWRITE(pin, HIGH)
#define DIGITALWRITE_LOW(pin)	DIGITALWRITE(pin, LOW)
#define DIGITALREAD(pin)	digitalRead(pin)
#define DELAY_MS(tm)		delay(tm)





#endif /* LOGUVNORPLATFORM_H_ */
