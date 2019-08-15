
/*
 * accel.h
 *
*/

#ifndef __ACCEL_H__
#define __ACCEL_H__

#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

class Accel : public MMA8452Q
{
public:
	void begin(void);
	void read(void);		// waits until available, then fills in the local variables.

public:
	int x;
	int y;
	int z;
};

#endif // __ACCEL_H__
