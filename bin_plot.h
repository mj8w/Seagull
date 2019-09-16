/*
 * lighting.h
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */
#include <FastLED.h>

#ifndef __SIMPLOT_H__
#define __SIMPLOT_H__

class Simplot
{
public:
	void setup(unsigned long int baud);
	void plot(int *data, size_t sz);
};

#endif // __SIMPLOT_H__

