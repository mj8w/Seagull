/*
 * bin_plot.h
 *
 *  Created on: Oct 23, 2016
 *      Author: mike
 */
#include <stdint.h>
#include <stddef.h>

#ifndef __BINPLOT_H__
#define __BINPLOT_H__

#define MAX_DATA_SZ 20 // The maximum number of bytes of data we support

class BinPlot
{
public:
	void setup(unsigned long int baud);
	void send(uint8_t header, uint8_t *data, size_t sz);
};

#endif // __BINPLOT_H__

