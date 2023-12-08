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


/* The LOGuvnor library has everything for your
 * LO governing needs.  Most important here are:
 *
 *  The LOGuvnor::Globals which give access to the
 *  driver; and
 *
 *  The various PIN_* definitions.
 *
 */
#include <LOGuvnor.h>

/*
 * Here am using the RotaryEncoder library, which can
 * be installed via the manager thing.
 *
 * You can use anything you like, just call the driver's
 * positionChangeEvent() as below when something of interest
 * happens.
 */
#include <RotaryEncoder.h>

/* *** Rotary encoder stuff... *** */

// create the instance
// use TWO03 mode when A and B signals are both LOW or HIGH in latch position.
// My encoders work well with "FOUR3", might try "FOUR0" as well if
// things go unhappy
RotaryEncoder rotEnc(PIN_ROTENC_A, PIN_ROTENC_B, RotaryEncoder::LatchMode::FOUR3);

// give it an ISR and flag
volatile bool checkRotaryEncoder = false;
void checkPosition() {
	rotEnc.tick(); // lib want you to call tick() to check the state.
	// we set a flag to say action is required
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
		0xff // termination flag -- impossible pin
	};
	uint8_t outputs[] = {
		PIN_STATUS,
		PIN_INDIC_nCHANSEL_1,
		PIN_INDIC_nCHANENA_1,
		PIN_INDIC_nCHANSEL_2,
		PIN_INDIC_nCHANENA_2,
		PIN_INDIC_nCHANSEL_3,
		PIN_INDIC_nCHANENA_3,
		0xff // termination flag -- impossible pin
	};

	// setup all the inputs
	uint8_t i = 0;
	while (inputs[i] != 0xff) {
		pinMode(inputs[i], INPUT_PULLUP);
		i++;
	}

	// reset i, and setup all the outputs
	i = 0;
	while (outputs[i] != 0xff) {
		pinMode(outputs[i], OUTPUT);
		digitalWrite(outputs[i], HIGH);
		i++;
	}

	// register interrupt routines for the knob
	attachInterrupt(digitalPinToInterrupt(PIN_ROTENC_A), checkPosition, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_ROTENC_B), checkPosition, CHANGE);

	// call begin on the guv'nor driver
	LOGuvnor::Globals::driver().begin();

}

/* *** main loop *** */
void loop() {

	LOGuvnor::Driver & LOGuvDriver = LOGuvnor::Globals::driver();

	// if encoder saw action, tell the driver
	if (checkRotaryEncoder) {
		checkRotaryEncoder = false;
		LOGuvDriver.positionChangeEvent(rotEnc.getPosition());
	}

	// always tick the driver to keep it alive and
	// doing what it does
	LOGuvDriver.tick();
}

