#include <Arduino.h>
#include "accel.h"
#include "lighting.h"
#include "filter.h"

Accel accel;
Lighting lights;
Filter filter;

void setup ()
{
    delay(300); // power-up safety delay
    lights.setup(40);    	// brightness
    accel.begin();
    Serial.begin(115200);

}

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





    // short delay in between readings/
    delay (10);

}
