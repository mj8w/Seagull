/*
 * simplot.cpp
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */
#include "bin_plot.h"

void Simplot::setup(unsigned long int baud)
{
	Serial.begin(baud);
}

void Simplot::plot(int *data, size_t sz)
// Plot using the simplot mechanism, to the serial port in such a way that Arduino Sloeber interface
// can produce an easy to use data plotting feature.
{
	static int buff[20];
	int* pb = buff;
	*pb++ = 0xCDAB;            //SimPlot packet header. Indicates start of data packet
	*pb++ = sz * sizeof(int);  //Size of data in bytes. Does not include the header and size fields

	for (size_t x = 0; x < sz;x++)
	{
		*pb++ = *data++;
	}
	//Header bytes + size field bytes + data
	Serial.write((uint8_t *)buff, 2 + 2 + (sz*sizeof(int)));
}


