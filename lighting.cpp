/*
 * lighting.cpp
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */

#include "lighting.h"

// LED strip info
// connections
#define LEDL     3
#define LEDR     4
#define NUM_LEDS    30    // per strip
#define CHIPSET     WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void Lighting::setup(int brightness)
{
	// It's important to set the color correction for your LED strip here,
	// so that colors can be more accurately rendered through the 'temperature' profiles
	FastLED.addLeds<CHIPSET, LEDL, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
	FastLED.addLeds<CHIPSET, LEDR, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
	FastLED.setBrightness( brightness );
	FastLED.setTemperature( HighNoonSun );

	for(int x = 0; x < NUM_LEDS;x++)
	{
		leds[x] = CRGB::White;
	}
}

void Lighting::show()
{
	FastLED.show();
}

void Lighting::brightness(int percent)
{
	int scaled = (percent * 255) + 50 / 100;	// scale 0-100 to 0-255
	FastLED.setBrightness(scaled);
	FastLED.show();
}

