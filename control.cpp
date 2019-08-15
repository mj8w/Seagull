/*
* Name: control.cpp
*/
#include "control.h"



void Timer::start(unsigned long delay_mS)
{
	timeout = millis() + delay_mS;
}

int Timer::complete()
{
	return (millis() > timeout);
}

void Control::setup(void)
{
	 /* Init protothread state. */
	 brightOut = 5;
}

int Control::get_brightness()
{
	return brightOut;
}

void Control::bump_y(int y)
{
	if(y > 5000)
	{
		Ty.start(500);	// 1/2 second
		Serial.println("DOWN");
		brightOut -= 10;
		if (brightOut < 0)
			brightOut = 0;
	}
	else if (y < -1000)
	{
		Ty.start(500);	// 1/2 second

		Serial.println("UP");
		brightOut += 10;
		if (brightOut > 100)
			brightOut = 100;
	}
}

void Control::bump_x(int x)
{
	if(x > 3000)
	{
		Tx.start(500);	// 1/2 second
		Serial.println("LEFT");
	}
	else if (x < -2000)
	{
		Tx.start(500);	// 1/2 second
		Serial.println("RIGHT");
	}
}

void Control::use_accel(int x, int y)
{
	if (Tx.complete())
		bump_x(x);
	if (Ty.complete())
		bump_y(y);
}
