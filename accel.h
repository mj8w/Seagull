
/*
 * accel.h
 *
*/

#ifndef __ACCEL_H__
#define __ACCEL_H__

#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
#include "filter.h"

class Accel : public MMA8452Q
{
public:
	void begin(void);
	void read(void);		// waits until available, then fills in the local variables.

	void filter(void);		// filter cycle for the three axis values
	void integrate(void);	// integrate cycle for the three axis values

public:
	int x;					// raw values from the accelerometer
	int y;
	int z;

	Q10P21 x_filtered;		// filtered values (about 1 second response)
	Q10P21 y_filtered;
	Q10P21 z_filtered;

	Q10P21 x_integrated;	// integrated values (about 100 second response)
	Q10P21 y_integrated;
	Q10P21 z_integrated;


	Q10P21 x_q10;			// raw values converted to Q10P21
	Q10P21 y_q10;
	Q10P21 z_q10;

private:
	Filter x_1_sec;
	Filter y_1_sec;
	Filter z_1_sec;
	Filter x_100_sec;
	Filter y_100_sec;
	Filter z_100_sec;

};

#endif // __ACCEL_H__
