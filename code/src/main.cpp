/*
 * LOGuvnorDriver.ino, part of the LOGuvnor project
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
 *  This is the main driver for the LOGuvnor library.
 *
 *  It's only jobs are to:
 *    * setup the various pins in use (as inputs outputs etc)
 *    * construct the rotary encoder object used and set that up
 *    * init the library Driver object
 *    * loop around, noticing if knob was turned (and telling the world) and ticking driver
 *
 * The end.
 *
 *
 */



#ifdef DESKTOP_BUILD2
/*
 * LOGuvnorDriver.ino, part of the LOGuvnor project
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
 *  This is the main driver for the LOGuvnor library.
 *
 *  It's only jobs are to:
 *    * setup the various pins in use (as inputs outputs etc)
 *    * construct the rotary encoder object used and set that up
 *    * init the library Driver object
 *    * loop around, noticing if knob was turned (and telling the world) and ticking driver
 *
 * The end.
 *
 *
 */

#include <LOGuvnor.h>
#include <RotaryEncoder.h>



/* *** Rotary encoder stuff... *** */

// create the instance
// use TWO03 mode when A and B signals are both LOW or HIGH in latch position.
RotaryEncoder rotEnc(PIN_ROTENC_A, PIN_ROTENC_B, RotaryEncoder::LatchMode::FOUR3);

// give it an ISR and flag
volatile bool checkRotaryEncoder = false;
void checkPosition()
{
  rotEnc.tick(); // just call tick() to check the state.
  checkRotaryEncoder = true;
}



/* *** setup *** */
void setup() {
	uint8_t inputs[] = {
			PIN_ROTENC_A,
			PIN_ROTENC_B,
			PIN_ROTSWITCH,
			PIN_SW_CHANSEL,
			PIN_SW_CHANEN,
			PIN_SW_FUNCTION,
			0xff
	};
	uint8_t outputs[] = {
			PIN_STATUS,
			PIN_INDIC_nCHANSEL_1,
			PIN_INDIC_nCHANENA_1,
			PIN_INDIC_nCHANSEL_2,
			PIN_INDIC_nCHANENA_2,
			PIN_INDIC_nCHANSEL_3,
			PIN_INDIC_nCHANENA_3,
			0xff
	};


	uint8_t i=0;
	while (inputs[i] != 0xff) {
		pinMode(inputs[i], INPUT); //_PULLUP);
		i++;
	}
	i=0;
	while (outputs[i] != 0xff) {
		pinMode(outputs[i], OUTPUT);
		digitalWrite(outputs[i], HIGH);
    i++;
	}

/*
  for (uint8_t i=0; i<10; i++) {

    digitalWrite(PIN_INDIC_nCHANENA_1, HIGH);
    delay(200);
    digitalWrite(PIN_INDIC_nCHANENA_1, LOW);
    delay(200);

  }
*/

	// register interrupt routine
	attachInterrupt(digitalPinToInterrupt(PIN_ROTENC_A), checkPosition, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_ROTENC_B), checkPosition, CHANGE);

	LOGuvnor::Driver & LOGuv = LOGuvnor::Globals::driver();
	LOGuv.begin();


}

/* *** main loop *** */
void loop() {
	// if encoder saw action, tell the driver
	if (checkRotaryEncoder) {
		checkRotaryEncoder = false;
		LOGuvnor::Globals::driver().positionChangeEvent(rotEnc.getPosition());
	}

	// always tick the driver to keep it alive and
	// doing what it does
	LOGuvnor::Globals::driver().tick();
}




#endif
