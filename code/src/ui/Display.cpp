/*
 * Display.cpp
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
#include "Display.h"
#include "../Globals.h"

namespace LOGuvnor {
namespace UI {

Display::Display() :
		_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), cursor_x(0), cursor_y(
				0), showingScreen(Screen::Type_BOUNDS), tick_count(0) {
#ifdef ENABLE_DEBUG_MESSAGES
	for(uint8_t i=0; i<MAX_QUEUED_MESSAGES; i++) {
		debug_messages[i].type = Debug::MessageType_BOUNDS;
	}
#endif
}

void Display::begin() {
	DEBUG_OUTLN("Display begins");
	_display.begin(DISPLAY_VOLTAGE, SCREEN_ADDRESS);

	_display.setRotation(2);
	clear();
}

void Display::setChannels(Channel *channelsList) {
	for (uint8_t i = 0; i < (uint8_t) Channel_BOUNDS; i++) {
		channels[i] = &channelsList[i];
	}
}

int16_t Display::width(void) const {
	return _display.width();
}
int16_t Display::height(void) const {
	return _display.height();
}

void Display::clear() {
	_display.clearDisplay();
	setCursor(0, 0);

	textNormal();
}

void Display::outputQueuedDebug() {

#ifdef ENABLE_DEBUG_MESSAGES
	uint8_t i=0;
	bool setCursorNow = true;
	while (i < MAX_QUEUED_MESSAGES && debug_messages[i].type != Debug::MessageType_BOUNDS) {

		if (i) {
			_display.print(F(" ")); // add a space
		}

		if (debug_messages[i].type == Debug::UInteger) {
			displayDebug(debug_messages[i].val_int, setCursorNow);
		} else {

			displayDebugString(debug_messages[i].val_str, setCursorNow);
		}

		debug_messages[i].type = Debug::MessageType_BOUNDS;
		i++;
		setCursorNow = false;
	}
	if (i) {
		draw();
	}
#endif
}

void Display::flush() {

	outputQueuedDebug();
	draw();
}
void Display::draw() {
	_display.display();
}

void Display::textSizeStandard() {
	_display.setTextSize(1);             // Normal 1:1 pixel scale
}

void Display::textSizeBig() {
	_display.setTextSize(2);
}

void Display::textNormal() {
	// Draw white text
	_display.setTextColor(COLOR_WHITE);
}

void Display::textInvert() {
	_display.setTextColor(COLOR_BLACK, COLOR_WHITE); // Draw 'inverse' text
}

void Display::setCursor(int16_t x, int16_t y) {
	cursor_x = x;
	cursor_y = y;
	_display.setCursor(x, y);

}

void Display::advanceCursor(int8_t deltax, int8_t deltay) {
	int8_t x = _display.getCursorX() + deltax;
	int8_t y = _display.getCursorY() + deltay;
	setCursor(x, y);
}
void Display::headerAllChannels(uint16_t d) {

	textSizeStandard();
	setCursor(100, 0);
	if (channels[2]->selected()) {
		textInvert();
	}
	_display.print(F(" 3 "));
	textNormal();
	advanceCursor(-65);
	if (d) {
		draw();
		DELAY_MS(d);
	}
	if (channels[1]->selected()) {
		textInvert();
	}
	_display.print(F(" 2 "));
	textNormal();
	advanceCursor(-65);
	if (d) {
		draw();
		DELAY_MS(d);
	}
	if (channels[0]->selected()) {
		textInvert();
	}
	_display.print(F(" 1 "));
	textNormal();
	//_display.drawLine(0, 9, width(), 9, COLOR_WHITE);

	draw();
	if (d) {
		DELAY_MS(d);
	}

}
void Display::showRoundedDigit(const Frequency &v, uint8_t digitIdx) {
	int vToShow = v.digit(digitIdx);
	if (vToShow < 9 && v.digit(digitIdx + 1) >= 5) {
		// round it up
		vToShow += 1;
	}
	_display.print(vToShow);
}

bool Display::abbreviatedValueHasDecimal(const Frequency &v) {
	switch (v.scale()) {
	case Frequency::TenMega:
		/* fall-through */
	case Frequency::TenKilo:
		return false;
	default:
		return true;
	}
}
void Display::showAbbreviatedValue(const Frequency &v) {
	textSizeBig();
	/*
	 * We don't have much screen real-estate, and want to
	 * have a quick view of all 3 channels.
	 *
	 * The frequency has 9 digits:
	 *   DIGITS: 000 000 000
	 *   INDEX:  012 345 678
	 *
	 * Depending on the scale of the frequency, we want to show
	 *  1: e.g. 0.1 GHz
	 *  2: e.g. 12 MHz or
	 *  2 (with decimal):  e.g. 4.7 kHz
	 *
	 * So we switch() on the scale and show appropriate digit
	 * indices.  The last digit is rounded, such that
	 *   149 MHz becomes 0.1 GHz and
	 *   150 MHz becomes 0.2 GHz
	 * which kinda sucks but I don't know what to do unless we want
	 *   1.5 CentaMegaHz or something equally awful.
	 */

	// show them digits
	switch (v.scale()) {
	case Frequency::HundredMega:
		_display.print(F("0."));
		showRoundedDigit(v, 0);
		break;
	case Frequency::HundredKilo:
		_display.print(F("0."));
		showRoundedDigit(v, 3);
		break;

	case Frequency::TenMega:
		_display.print((int) v.digit(1));
		showRoundedDigit(v, 2);

		break;
	case Frequency::TenKilo:
		_display.print((int) v.digit(4));
		showRoundedDigit(v, 5);
		break;

	case Frequency::Mega:
		_display.print((int) v.digit(2));
		_display.print(F("."));
		showRoundedDigit(v, 3);
		break;
	case Frequency::Kilo:
		_display.print((int) v.digit(5));
		_display.print(F("."));
		showRoundedDigit(v, 6);
		break;

	}

	// small font, show the units
	textSizeStandard();
	advanceCursor(1, 7);

	switch (v.scale()) {
	case Frequency::HundredMega:
		_display.print(F("G"));
		break;
	case Frequency::TenMega:
		/* fall - through */
	case Frequency::Mega:
		/* fall - through */
	case Frequency::HundredKilo:
		/* fall - through */
		_display.print(F("M"));
		break;

	case Frequency::TenKilo:
		/* fall - through */
	case Frequency::Kilo:
		_display.print(F("k"));
		break;
	}
}

void Display::showError(ERR_MSG_STR errmsg) {
	loadedScreen(Screen::Error);
	clear();
	textSizeStandard();
	setCursor(2, 3);
	_display.print(errmsg);
	draw();
}
#define SPLASH_BASE_DELAY_MS	120
void Display::showSplash() {
	loadedScreen(Screen::Splash);
	clear();
	textSizeBig();
	setCursor(2, 10);
#ifndef SPLASH_BASE_DELAY_MS
	_display.print(F("LO Guv'nor"));
	draw();
#else
	_display.print(F("L"));
	draw();
	DELAY_MS(SPLASH_BASE_DELAY_MS * 2);
	_display.print(F("O "));
	draw();
	DELAY_MS(SPLASH_BASE_DELAY_MS * 4);

	_display.print(F("Guv'"));
	draw();
	DELAY_MS(SPLASH_BASE_DELAY_MS);
	_display.print(F("nor"));
	draw();
#endif

	DELAY_MS(350);
	headerAllChannels(110);
	flush();
}

void Display::displayDebug(uint32_t v, bool setcurs) {
	if (setcurs) {
		textNormal();
		textSizeStandard();
		setCursor(5, 25);
	}
	_display.print(v);
}
void Display::displayDebugString(DBG_MSG_STR s, bool setcurs) {
	if (setcurs) {
		textNormal();
		textSizeStandard();
		setCursor(5, 25);
	}
	_display.print(s);
}

void Display::showSummary() {
	loadedScreen(Screen::Summary);
	clear();
	headerAllChannels(0);

	const uint8_t xcoords[] = { 0, 42, 85 };
	uint8_t xpos = 0;
	for (uint8_t i = 0; i < (uint8_t) Channel_BOUNDS; i++) {

		textSizeBig();

		xpos = xcoords[i] + (abbreviatedValueHasDecimal(
								channels[i]->frequency()) ? 0 : 8);
		setCursor(xpos, 10);
		showAbbreviatedValue(channels[i]->frequency());

		if (channels[i]->enabled()) {

			textSizeStandard();
			setCursor(xcoords[i] + 12, 25);
			_display.print(F("on"));
		}
	}

	flush();
}

void Display::showChannel(Channel &channel, uint8_t selectedUnits,
		bool highlightDigit, bool editing) {

	loadedScreen(Screen::Channel);

	// Show header, eg.
	// Ch 1   ON   kHz
	clear();
	textSizeStandard();
	setCursor(0, 0);
	_display.print(F(" Ch "));
	_display.print(1 + (int) channel.id());

	setCursor(50, 0);
	if (channel.enabled()) {
		advanceCursor(3, 0);
		_display.print(F("ON"));
	} else {
		_display.print(F("off"));
	}

	setCursor(82, 0);
	Frequency::Scale scale = channel.frequency().scale();
	// _display.print(F(" "));
	switch (scale) {
	case Frequency::Kilo:
		/* fall-through */
	case Frequency::TenKilo:
		/* fall-through */
	case Frequency::HundredKilo:
		_display.print(F("k"));
		break;
	case Frequency::Mega:
		/* fall-through */
	case Frequency::TenMega:
		/* fall-through */
	case Frequency::HundredMega:
		_display.print(F("M"));
		break;
	}
	_display.print(F("Hz "));

	// if it isn't "pure" (M|k)?Hz,
	// indicate the num digits
	if ((int) scale % 3) {
		_display.print(F("^"));
		_display.print((int) scale);
	}

	setCursor(0, 9);
	textSizeBig();

	uint8_t digIdx = 0;
	uint8_t unitIdx;
	uint8_t digValue;
	bool haveDigits = false;
	bool shouldHighlight = false;

	while (digIdx < channel.frequency().numDigits()) {
		unitIdx = (channel.frequency().numDigits() - 1) - digIdx;

		if (highlightDigit) {
			if ((unitIdx == selectedUnits) || editing) {
				shouldHighlight = true;
				textInvert();
			} else {
				shouldHighlight = false;
				textNormal();
			}
		}
		if (editing) {
			_display.drawLine(0, 8, width() - 20, 8, COLOR_WHITE);
		}

		digValue = channel.frequency().digit(digIdx);

		if ((!haveDigits) && digValue == 0) {
			_display.print(F(" "));
		} else {
			haveDigits = true;
			_display.print((int) digValue);
		}

		digIdx++;
	}

	if (shouldHighlight) {
		textNormal();
	}

	textSizeStandard();

	flush();
}

void Display::debugMessage(uint32_t v) {
	Debug::QueuedMessage msg { v, 0, Debug::UInteger };
	enqueue(msg);
}
void Display::debugMessage(DBG_MSG_STR s) {
	Debug::QueuedMessage msg { 0, s, Debug::String };
	enqueue(msg);

}
bool Display::enqueue(Debug::QueuedMessage &msg) {
#ifdef ENABLE_DEBUG_MESSAGES
	for (uint8_t i=0; i<MAX_QUEUED_MESSAGES; i++) {
		if (debug_messages[i].type == Debug::MessageType_BOUNDS) {
			debug_messages[i].type = msg.type;
			debug_messages[i].val_int = msg.val_int;
			debug_messages[i].val_str = msg.val_str;

			return true;
		}
	}
#endif

	return false;
}

void Display::tick() {
	tick_count++;
#ifdef ENABLE_SCROLLERS
	/* I've got them bytes... why not have a scroller?? */
	if ((showingScreen == Screen::Channel) // always on for channel details
		||
		(showingScreen == Screen::Summary && !Globals::ui().numChannelsEnabled())
	){
		int16_t pos = width() + 15 - (((tick_count / 2)) % (width() + 140));
		// setCursor(0,25);
		_display.fillRect(0, 25, width(), 15, COLOR_BLACK);
		setCursor(pos, 25);
		if (showingScreen == Screen::Channel) {
			_display.print(F("Edit me Guv'nor"));
		} else {
			_display.print(F("  LO Guv'nor"));
		}
		draw();

	}
#endif

}
void Display::loadedScreen(Screen::Type tp) {

	if (tp != showingScreen) {
		tick_count = 0;
	}

	showingScreen = tp;
}
void Display::rectangle(int16_t x, int16_t y, int16_t w, int16_t h,
		int16_t radius) {
	if (radius) {
		_display.drawRoundRect(x, y, w, h, radius, COLOR_WHITE);
	} else {
		_display.drawRect(x, y, w, h, COLOR_WHITE);
	}
}

#ifdef DESKTOP_BUILD

#define DUMMYDISPLAY_VERBOSE_DEBUG

#ifdef DUMMYDISPLAY_VERBOSE_DEBUG
#define DUMMY_DEBUG(...) DEBUG_OUT("DummyDisplay: "); DEBUG_OUT(__VA_ARGS__)
#define DUMMY_DEBUGLN(...) DEBUG_OUT("DummyDisplay: "); DEBUG_OUTLN(__VA_ARGS__)
#else
#define DUMMY_DEBUG(...)
#define DUMMY_DEBUGLN(...)
#endif

void DummyDisplay::begin(uint8_t a, uint8_t b) {
	DUMMY_DEBUGLN("begin");
}

void DummyDisplay::clearDisplay() {
	DUMMY_DEBUGLN("clear");
}

void DummyDisplay::setTextSize(uint8_t s) {
	DUMMY_DEBUG("setTextSize ");
	DEBUG_OUTLN((int )s);
}

void DummyDisplay::setTextColor(uint8_t c, uint8_t bg) {
	DUMMY_DEBUG("setTextColor ");
	DEBUG_OUT((int )c);
	DEBUG_OUT(", ");
	DEBUG_OUTLN((int )bg);
}

void DummyDisplay::setCursor(uint8_t x, uint8_t y) {
	DUMMY_DEBUG("setCursor ");
	DEBUG_OUT((int )x);
	DEBUG_OUT(",");
	DEBUG_OUTLN((int )y);
}

void DummyDisplay::drawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
		uint8_t radius, uint8_t col) {
	DUMMY_DEBUGLN("draw roundrect");
}

void DummyDisplay::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
		uint8_t col) {
	DUMMY_DEBUGLN("draw rect");
}

void DummyDisplay::drawLine(uint8_t x, uint8_t y, uint8_t x2, uint8_t y2,
		uint8_t col) {
	DUMMY_DEBUGLN("draw line");

}

void DummyDisplay::display() {
	DUMMY_DEBUGLN("display");
}

void DummyDisplay::print(uint8_t i) {
	DEBUG_OUT((int )i);
}

void DummyDisplay::print(const char *s) {
	DEBUG_OUTLN(s);
}

#endif

} /* namespace UI */
} /* namespace LOGuvnor */
