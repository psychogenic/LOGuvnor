/*
 * pins.h
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

#ifndef SRC_PINS_H_
#define SRC_PINS_H_


#define PIN_URX			0

#define PIN_UTX			1
#define PIN_ROTENC_A	2
#define PIN_ROTENC_B	3
#define PIN_ROTSWITCH	4
#define PIN_SW_CHANSEL	5
#define PIN_SW_CHANEN	6
#define PIN_SW_FUNCTION	7
#define PIN_STATUS		8

#define PIN_EXTRA1		9
#define PIN_EXTRA2		10

#define PIN_MOSI		11
#define PIN_MISO		12
#define PIN_SCK			13

#define PIN_INDIC_nCHANSEL_3	A0
#define PIN_INDIC_nCHANENA_3	A1
#define PIN_INDIC_nCHANSEL_2	A2
#define PIN_INDIC_nCHANENA_2	A3
#define PIN_INDIC_nCHANSEL_1	10 /* A6 A7 ANALOG INPUTS ONLY, ugh ! */
#define PIN_INDIC_nCHANENA_1	9



#endif /* SRC_PINS_H_ */
