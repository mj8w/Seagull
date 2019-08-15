/****************************************************************************
* Name: filter.h
* FIR filter algorithms for use in CPP
*
*   This module provides functions to implement Finite Impulse Response (FIR)
*   These functions use most or all of the following input parameters:
*
*       input    - the input sample data
*       ntaps    - the number of taps in the filter   
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

#ifndef __FILTER_H__
#define __FILTER_H__

#define TAPS 13

class Filter
{
public:
	void setup(void);
	int fir(int input);
	int l(int input);
	int u(int input);


private:
	int z[TAPS];
	int index = 0;
	int w = 4;		// width of lulu operators.
};

#endif // __FIR_FILTER_H__


