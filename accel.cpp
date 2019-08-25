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

	read();

	x_1_sec.setup(20, x_q10);
	y_1_sec.setup(20, y_q10);
//	z_1_sec.setup(20, z_q10);

	x_100_sec.setup(500, x_q10);
	y_100_sec.setup(500, y_q10);
//	z_100_sec.setup(500, z_q10);

}

void Accel::read(void)
{
	while(!available())
		;
	x = getX();
	y = getY();
//	z = getZ();

	x_q10 = Q10P21_ONE * x;
	y_q10 = Q10P21_ONE * y;
//	z_q10 = Q10P21_ONE * z;


}

void Accel::filter(void)
{
	x_filtered = x_1_sec.leaky(x_q10);
	y_filtered = y_1_sec.leaky(y_q10);
//	z_filtered = z_1_sec.leaky(z_q10);

}

void Accel::integrate(void)
{

	x_integrated = x_100_sec.leaky(x_q10);
	y_integrated = y_100_sec.leaky(y_q10);
//	z_integrated = z_100_sec.leaky(z_q10);
}

