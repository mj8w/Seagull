
/*
 * lighting.h
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */
#include <FastLED.h>

#ifndef __LIGHTING_H__
#define __LIGHTING_H__

class Lighting
{
public:
	void setup(int brightness);
	void show();
	void brightness(int percent);
};

#endif
