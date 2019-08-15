/****************************************************************************
* Name: filter.c
* Synopsis: FIR filter algorithms for use in C
* Description:
*   This module provides functions to implement Finite Impulse Response (FIR)
*   filters using a variety of algorithms.  
*   These functions use most or all of the following input parameters:
*
*       input    - the input sample data
*       ntaps    - the number of taps in the filter   
*
*
*
*
*       h[]      - the FIR coefficient array
*       z[]      - the FIR delay line array 
*       *p_state - the "state" of the filter; initialize this to 0 before
*                  the first call
*
*   The functions fir_split, fir_double_z and fir_double_h are all 
* 	fairly efficient ways to implement FIR filters in C.
* 
*****************************************************************************
* Copyright 2000-2015 by Grant R. Griffin
* Permission to use, copy, modify, distribute and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice and this license appear in all source copies. 
* THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF
* ANY KIND. See http://www.dspguru.com/wide-open-license for more information.
*
*****************************************************************************/

#include "filter.h"

void Filter::setup(void)
{
	index = 0;
	for (int i = 0; i < TAPS; i++) { z[i] = 0;	}
}

int Filter::fir(int input)
/*
 * fir: Calculate the FIR filter on the input data. There are two loops to
 * keep the circular buffer logic out of the calculation loops.
*/
{
	const int coeff[TAPS] =
	{ -1646, -2943, -3370, -1745, 1680,  5186,  6672,  5186,  1680, -1745, -3370, -2943, -1646 };

	int accum = 0;
    int const *ph = coeff;
    int *pz = z + index;
    int end_ntaps = TAPS - index;

    *pz = input;
    for (int i = 0; i < end_ntaps; i++)
    {
        accum += *ph++ * *pz++;
    }

    pz = z;
    for (int i = 0; i < index; i++)
    {
        accum += *ph++ * *pz++;
    }

    /* decrement the state, wrapping if below zero */
    if (--index < 0)
    	index += TAPS;

    return accum;
}

int min(int *pz, const int sz)
{
	int mm = 32767;
	for (int i = 0; i < sz; i++, pz++)
		if (*pz < mm) mm = *pz;
	return mm;
}


int max(int *pz, const int sz)
{
	int mx = -32767;
	for (int i = 0; i < sz; i++, pz++)
		if (*pz > mx) mx = *pz;
	return mx;
}

int L(int *pz, int W)
{
	// find the lower limit of the upper values
	int ll = 32767;
	for (int *pm = pz-W; pm < pz; pm++)
	{
		int mx = max(pm, W+1);
		if (mx < ll) ll = mx;
	}
	return ll;
}

int U(int *pz, int W)
{
	// find the upper limit of the lowest values
	int uu = -32767;
	for (int *pm = pz-W; pm < pz; pm++)
	{
		int mm = min(pm, W+1);
		if (mm > uu) uu = mm;
	}
	return uu;
}

int Filter::u(int input)
{
	// shift the existing data, then perform the lulu on the data...
	int *lastz = z + TAPS - 1;
	int *pz;
    for (pz = lastz; pz > z; pz--)
    {
        *pz = *(pz-1);
    }
    *pz = input;

    // the midpoint of the data is where the smoother is focused.
    return U(z+5,4);
}

int Filter::l(int input)
{
	// shift the existing data, then perform the lulu on the data...
	int *lastz = z + TAPS - 1;
	int *pz;
    for (pz = lastz; pz > z; pz--)
    {
        *pz = *(pz-1);
    }
    *pz = input;

    // the midpoint of the data is where the smoother is focused.
    return L(z+5,4);
}
