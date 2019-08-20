// Name: filter.cpp

#include "filter.h"

void Filter::setup(float alpha_val, Q10P21 sample = Q10P21_ONE)
{
	alpha = (Q10P21) (alpha_val * Q10P21_ONE);
	accum = sample;
}

/* Leaky integrator 'filter' */
Q10P21 Filter::leaky(Q10P21 sample)
{
	accum += alpha * (sample-accum);
}
