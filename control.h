/*
* Name: control.h
*/


#ifndef __CONTROL_H__
#define __CONTROL_H__
#include <FastLED.h>


class Timer
{
public:
	void start(unsigned long delay_mS);
	int complete();
private:
	unsigned long timeout;
};

class Control
{
public:
	void setup(void);
	int get_brightness();
	void use_accel(int x, int y);


private:
	void bump_y(int y);
	void bump_x(int x);

	int brightOut = 0;		//
	Timer Tx, Ty;

};

#endif // __CONTROL_H__
