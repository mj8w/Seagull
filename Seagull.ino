#include <Arduino.h>
#include "accel.h"
#include "lighting.h"
#include "simplot.h"
#include "filtering.h"

Accel accel;
Lighting lights;
Simplot plot;
Filters filter_x;
Filters filter_y;
Filters filter_z;

void setup ()
{
    delay (300); // power-up safety delay
    plot.setup (115200);
    lights.setup (12);    	// brightness
    accel.begin ();

    // take our first reading to initialize filters internal history buffers
    accel.read (); // update the 3-axis from accelerometer

    filter_x.begin (12);		// samples from signed 12 bit source
    filter_x.setup (accel.x, -1500, 1500, 100);

    filter_y.begin (12);		// samples from signed 12 bit source
    filter_y.setup (accel.y, -1500, 1500, 100);

    filter_z.begin (12);		// samples from signed 12 bit source
    filter_z.setup (accel.z, -1500, 1500, 100);
}

// filtered values
int fx = 0;
int fy = 0;
int fz = 0;

void loop ()
{
    // continually call the accelerometer 'tap' to check for taps and double taps.

    // tipping wings should lead to small changes in one of the axes G forces
    // as the axis becomes tipped toward the ground.
    // look for the change in direction, so need to check at a rate that
    // allows for a significant change rate. But also ignore jumps in values from
    //   being bumped.

    // - reject changes bigger than "allowable" (but change up to 'allowable' amount)
    // - average the results over a long period of time
    //     time period chosen so that a slow change can be detected in single sample
    //     if the change threshold is reached, do something (brightness?)

    // try to avoid floating point
    lights.show ();
    accel.read (); // update the 3-axis from accelerometer

    fx = filter_x.clip (accel.x);
//	fy = filter_y.clip(accel.y);
//	fz = filter_z.clip(accel.z);

//	fx = filter_x.limit_slew(fx);
//	fy = filter_y.limit_slew(fy);
//	fz = filter_z.limit_slew(fz);

    Serial.println (fx);

    // short delay in between readings/
    delay (10);

}
