/*
 * LOGuvnorTypes.h
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

#ifndef LOGUVNORTYPES_H_
#define LOGUVNORTYPES_H_

#include <stdint.h>
#include "LOGuvnorConfig.h"

#define NUMDIGITS_MAX	9

#define SELECTED_UNITS_NA 	NUMDIGITS_MAX + 5 /* anything above max, really */

#define FLASH_RESIDENT_STR	 const __FlashStringHelper*
#define DBG_MSG_STR	FLASH_RESIDENT_STR
#define ERR_MSG_STR	FLASH_RESIDENT_STR

namespace LOGuvnor {

// behaviour type IDs
namespace Behaviour {
namespace Type {
	typedef enum behavtypesenum {
		SplashScreen = 0,
		Summary = 1,
		DetailView = 2,
		DetailEdit = 3,
		Type_BOUNDS = 4
	} ID;
} /* namespace Type */
} /* namespace Behaviour */

typedef enum channelidenum {
	Channel_1 = 0,
	Channel_2 = 1,
	Channel_3 = 2,

	Channel_BOUNDS=SI5351_NUM_CHANNELS
} ChannelID;

typedef enum switchidenum {
	Button_ChannelSelect = 0,
	Button_ChannelEnable = 1,
	Button_Function = 2,
	Button_RotaryEncoder = 3,

	Button_BOUNDS=4

} ButtonID;


typedef uint8_t 	Pin;
typedef uint32_t	FrequencyHz;
typedef int16_t		RotEncoderPosition;



}



#endif /* LOGUVNORTYPES_H_ */
