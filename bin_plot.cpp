/*
 * simplot.cpp
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */
#include "bin_plot.h"

void BinPlot::setup(unsigned long int baud)
{
	Serial.begin(baud);
}

void BinPlot::send(uint8_t header, uint8_t *data, size_t sz)
// Send binary data to the serial port for use in plotting using Datascope.
{
	static uint8_t buff[MAX_DATA_SZ];
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


