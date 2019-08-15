/*
 * accel.h
 *
*/

#ifndef _FILTE_H_
#define _FILTE_H_

#define PREV_SAMPLES_RETAINED 1


class Filters
{
public:

	void begin(int sample_size_bits);
		// 	setup the defaults and initialize states

	void setup(int initial_sample, int min, int max, int slew);
		// 	setup initial values.
		// 	initial_sample is needed to initialize history values to prevent
		//	an initial slew from an arbitrary value

	int clip(int sample);
		//	return sample limited to the minimum and maximum values

	int limit_slew(int sample);
		//	return sample limited in slew from previous sample

public:
	// range variables
	int minimum;
	int maximum;

	// slew limit variables
	int max_slew;

private:
	int prev[PREV_SAMPLES_RETAINED];
};

#endif // _FILTE_H_

