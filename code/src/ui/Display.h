/*
 * Display.h
 *
 *  Created on: Nov 27, 2023
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
 * The Display is the OLED display.
 *
 * It both a wrapper around the low-level
 * driver for the OLED display (an SSD1306
 * based module, nicely handled by Adafruit
 * libraries), and the home for all the code
 * that organizes the various screens.
 *
 * This could've (maybe should've) been broken
 * up into modes, similar to the behaviour, but
 * it's so low-level in terms of moving the cursor
 * around and setting fonts etc. that it's just
 * all clumped here in the most monstrous class
 * of the project. meh.
 *
 */

#ifndef UI_DISPLAY_H_
#define UI_DISPLAY_H_

#include "../includes/projectIncludes.h"
#include "Channel.h"
namespace LOGuvnor {
namespace UI {
#ifdef DESKTOP_BUILD

/*
 * I like to compile stuff on desktop prior to
 * moving to the actual embedded--easier to get
 * going and for initial debug.
 *
 * So the dummy display class is just used in that
 * case, ignore me.
 *
 */
class DummyDisplay {
public:
	DummyDisplay(uint8_t w, uint8_t h, void * wire, uint8_t rst) {}
	void begin(uint8_t a, uint8_t b);
	void clearDisplay();
	void setTextSize(uint8_t s);
	void setTextColor(uint8_t c, uint8_t bg=0);
	void setCursor(uint8_t x, uint8_t y);
	void drawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t radius, uint8_t col);
	void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t col);
	void drawLine(uint8_t x, uint8_t y, uint8_t x2, uint8_t y2, uint8_t col);
	void display();

	void print(uint8_t i);
	void print(const char * s);

	void setRotation(uint8_t r) {}
	uint8_t width() const { return 128;}
	uint8_t height() const { return 32;}
	uint8_t getCursorX() { return 4;}
	uint8_t getCursorY() { return 2;}


};

// more dummy values
#define COLOR_WHITE 		1
#define COLOR_BLACK 		0
#define DISPLAY_VOLTAGE		1

#ifdef DESKTOP_USESSD1306
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
typedef Adafruit_SSD1306 RawDisplayType;
#else
typedef DummyDisplay RawDisplayType;
#endif /* adafruit stuff */

#else

// adafruit types and defs
#define COLOR_WHITE 		SSD1306_WHITE
#define COLOR_BLACK 		SSD1306_BLACK
#define DISPLAY_VOLTAGE		SSD1306_SWITCHCAPVCC

typedef Adafruit_SSD1306 RawDisplayType;

#endif

#define MAX_QUEUED_MESSAGES		5
namespace Debug {
	typedef enum {
		UInteger = 0,
		String = 1,
		MessageType_BOUNDS = 2,
	} MessageType;

	// could use a union here, whatev's: disabled
	// in production, for space
	typedef struct {
		uint32_t val_int;
		DBG_MSG_STR val_str;
		MessageType type;
	} QueuedMessage;
} /* namespace Debug */

namespace Screen {
	typedef enum screentype {
		Splash = 0,
		Summary = 1,
		Channel = 2,

		Error = 3,
		Type_BOUNDS = 4

	} Type ;
} /* namespace Screen */


class Display {
public:

	Display();

	// lifecycle
	void begin();
	void tick();


	// the 3 mode screens: splash, summary and details/editing
	void showSplash();
	void showSummary();
	void showChannel(Channel & channel,
			uint8_t selectedUnits=SELECTED_UNITS_NA,
			bool highlightDigit=false,
			bool editing=false);
	void showError(ERR_MSG_STR errmsg);


	// clear and draw immediate
	void clear();
	void flush();
	// weak ref to channels list, used internally
	void setChannels(Channel * channelsList);

	void debugMessage(uint32_t v);
	void debugMessage(DBG_MSG_STR s);
private:

	void loadedScreen(Screen::Type tp);





	void headerAllChannels(uint16_t delay=50);
	bool abbreviatedValueHasDecimal(const Frequency & v);
	void showAbbreviatedValue(const Frequency & v);
	void showRoundedDigit(const Frequency & v, uint8_t digitIdx);

	// wrappers for low-level ops like setting fonts and moving cursor
	int16_t width(void) const;
	int16_t height(void) const;
	void textSizeStandard();
	void textSizeBig();
	void textNormal();
	void textInvert();
	void setCursor(int16_t x, int16_t y);
	void advanceCursor(int8_t deltax, int8_t deltay=0);
	void draw();
	void rectangle(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius=0);

	void displayDebug(uint32_t v, bool setcursor=true);
	void displayDebugString(DBG_MSG_STR s, bool setcursor=true);

	bool enqueue(Debug::QueuedMessage & msg);
	void outputQueuedDebug();


	Channel * channels[(uint8_t)Channel_BOUNDS];
	RawDisplayType _display;
	int8_t cursor_x;
	int8_t cursor_y;
#ifdef ENABLE_DEBUG_MESSAGES
	Debug::QueuedMessage debug_messages[MAX_QUEUED_MESSAGES];
#endif
	Screen::Type showingScreen;
	uint16_t tick_count;


};

} /* namespace UI */
} /* namespace LOGuvnor */

#endif /* UI_DISPLAY_H_ */
