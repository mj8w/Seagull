/*
 * accel.cpp
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */
#include "accel.h"

void Accel::begin(void)
{
	Wire.begin();
	MMA8452Q::begin();
	setScale(SCALE_2G); // 0 to 2 G. +/- 1024 correspond to +/- 1G (gravity)
	setDataRate(ODR_100); // 100 Hz sample rate
}

void Accel::read(void)
{
	while(!available())
		;
	x = getCalculatedX();
	y = getCalculatedY();
	z = getCalculatedZ();
}


