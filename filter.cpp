// Name: filter.cpp

#include <Arduino.h>

#include "filter.h"

void Filter::setup(long invalpha_val, Q10P21 sample = Q10P21_ONE)
{
	invalpha = invalpha_val;

	// 	Serial.print("alpha ");
	//	Serial.println(alpha);
	accum = sample;
}

/* Leaky integrator 'filter' */
Q10P21 Filter::leaky(Q10P21 sample)
{
	accum += (sample - accum) / invalpha;
	return accum;
}
