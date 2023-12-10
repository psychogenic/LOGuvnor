/*
 * SimulatedUser.ino, part of the LOGuvnor project
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

#include <LOGuvnor.h>
#include <RotaryEncoder.h>


  // use TWO03 mode when PIN_IN1, PIN_IN2 signals are both LOW or HIGH in latch position.
RotaryEncoder rotEnc(PIN_ROTENC_A, PIN_ROTENC_B, RotaryEncoder::LatchMode::TWO03);

volatile bool checkRotaryEncoder = false;
void checkPosition()
{
  rotEnc.tick(); // just call tick() to check the state.
  checkRotaryEncoder = true;
}


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
		pinMode(inputs[i], INPUT);
		i++;
	}

	i=0;
	while (outputs[i] != 0xff) {
		pinMode(outputs[i], OUTPUT);
		digitalWrite(outputs[i], HIGH);
	}

	LOGuvnor::Driver & LOGuv = LOGuvnor::Globals::driver();
	LOGuv.setup();

	// register interrupt routine
	attachInterrupt(digitalPinToInterrupt(PIN_ROTENC_A), checkPosition, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_ROTENC_B), checkPosition, CHANGE);

	LOGuv.begin();


}

void toggleChanEnable() {

  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_ChannelEnable, true);
  LOGuvnor::Globals::driver().tick();
  delay(10);
  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_ChannelEnable, false);
  LOGuvnor::Globals::driver().tick();
  delay(10);
}


void toggleChanSelect() {
  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_ChannelSelect, true);
  LOGuvnor::Globals::driver().tick();
  delay(10);
  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_ChannelSelect, false);
  LOGuvnor::Globals::driver().tick();
  delay(10);
}

void toggleFunction() {
  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_Function, true);
  LOGuvnor::Globals::driver().tick();
  delay(10);
  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_Function, false);
  LOGuvnor::Globals::driver().tick();
  delay(10);
}

void toggleKnobButton() {
  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_RotaryEncoder, true);
  LOGuvnor::Globals::driver().tick();
  delay(10);
  LOGuvnor::Globals::driver().behaviour()->buttonChangeEvent(LOGuvnor::Button_RotaryEncoder, false);
  LOGuvnor::Globals::driver().tick();
  delay(10);
}


void changeKnobPosition(int pos) {
  LOGuvnor::Globals::driver().behaviour()->knobChangeEvent(pos);
  LOGuvnor::Globals::driver().tick();
  delay(10);
}

void incrementKnob(int8_t by) {
  LOGuvnor::Globals::driver().behaviour()->knobChangeEvent( LOGuvnor::Globals::driver().behaviour()->position() + by);
  LOGuvnor::Globals::driver().tick();
  delay(10);
}


void loop() {
	if (checkRotaryEncoder) {
		checkRotaryEncoder = false;
		LOGuvnor::Globals::driver().positionChangeEvent(rotEnc.getPosition());
	}
	LOGuvnor::Globals::driver().tick();
}

void ignored() {
  for(uint8_t i=0; i<10; i++) {
    LOGuvnor::Globals::driver().tick();
  }

  incrementKnob(1);
  if (LOGuvnor::Globals::driver().mode() == LOGuvnor::Behaviour::Type::Summary) {
    toggleChanEnable();
    toggleChanSelect();
    incrementKnob(-2);
    delay(1000);
    toggleKnobButton();
    incrementKnob(3);
    delay(2000);
    incrementKnob(-1);
    toggleKnobButton();
    incrementKnob(7);
    toggleKnobButton();
    for(;;) {
      incrementKnob(1);
      delay(200);
    }
  }

}

