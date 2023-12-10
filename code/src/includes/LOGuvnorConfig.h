/*
 * LOGuvnorConfig.h
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

#ifndef SRC_LOGUVNORCONFIG_H_
#define SRC_LOGUVNORCONFIG_H_

/* default frequencies per channel, in Hz */
#define FREQUENCY_DEFAULT_CHANNEL_1			7500
#define FREQUENCY_DEFAULT_CHANNEL_2			42000
#define FREQUENCY_DEFAULT_CHANNEL_3			10000000ULL

/* if the digit selection seems unnatural/to go the
 * wrong way, uncomment this define and it'll flip it.
 */
//#define FREQEDIT_DIGITSELECTKNOB_INVERT

/*
 * In development, may want to comment out
 * DIE_ON_SIGGEN_ERROR
 * When defined, will flash status if problem
 * bringing up si5351
 */
#define DIE_ON_SIGGEN_ERROR

#define STATUS_LED_ON_DURING_OPERATION		false /* true or false */
#define STATUS_LED_HEARTBEAT_TICKPERIOD		100 /* smaller is faster */


#define SI5351_CORRECTIONFACTOR		-1245 /* tested deviation @ 10MHz */
#define SI5351_DRIVESTRENGTH		SI5351_DRIVE_4MA /* from library 2,4,6 or 8mA*/

// TOO FAT: define ENABLE_DEBUG_MESSAGES

/* Scrolling text: a luxury... if you really need some room,
 * save over two hundred bytes by disabling this define
 */
#define ENABLE_SCROLLERS

/* DEBUG_SERIAL_BAUDRATE
 * undef to disable serial debug
 */
#define DEBUG_SERIAL_BAUDRATE	157200

#define SI5351_NUM_CHANNELS		3

#define ERROR_MESSAGEFLASH_MS	700

#define FREQUENCY_MINIMUM_HZ	1000 /* 2000 */
#define FREQUENCY_MAXIMUM_HZ	230000000ULL


#define SCREEN_WIDTH 		128 // OLED display width, in pixels
#define SCREEN_HEIGHT 		32 // OLED display height, in pixels
#define OLED_RESET     		-1 		// Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 		0x3C 	///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


#endif /* SRC_LOGUVNORCONFIG_H_ */
