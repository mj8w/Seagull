// Name: filter.h

#ifndef __FILTER_H__
#define __FILTER_H__

typedef long Q10P21; // number with 10 bits point 21 bits
#define Q10P21_ONE ((Q10P21) 1 << 21)	// "1.0" in Q10P21 format

class Filter
{
public:
	void setup(float alpha, Q10P21 sample = Q10P21_ONE);
	Q10P21 leaky(Q10P21 sample);
private:
	Q10P21 alpha;
	Q10P21 accum;
};

#endif // __FIR_FILTER_H__


