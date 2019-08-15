/*
 * accel.cpp
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */
#include "filtering.h"

void Filters::begin(int sample_size_bits)
{
	// default values set to something reasonable but very permissive
	maximum = (1<<sample_size_bits)-1;
	minimum = -maximum;
	max_slew = maximum / 2;

	int midpoint = minimum + ((maximum - minimum)/2);
	for (int i = 0; i < PREV_SAMPLES_RETAINED; i++)
		prev[i] = midpoint;
}

void Filters::setup(int initial_sample, int min, int max, int slew)
{
	for (int i = 0; i < PREV_SAMPLES_RETAINED; i++)
		prev[i] = initial_sample;

	maximum = max;
	minimum = min;
	max_slew = slew;
}

int Filters::clip(int sample)
{
    if (sample < minimum)
        return(minimum);
    else if (sample > maximum)
		return(maximum);
   	return(sample);
}

int Filters::limit_slew(int sample)
{
	int slewed = sample - prev[0];
    if (slewed < -max_slew)
    	prev[0] = prev[0] - max_slew;
    else if (slewed > max_slew)
    	prev[0] = prev[0] + max_slew;
    else
		prev[0] = sample;

	return prev[0];
}
