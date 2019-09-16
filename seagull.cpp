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
    lights.setup();    	// brightness
    accel.begin();
    Serial.begin(115200);
}

short brightness = 40;

unsigned long interval = 10; //mS
unsigned long done_time;
unsigned long now;

void loop ()
{
    // TODO: continually call the accelerometer 'tap' to check for taps and double taps.

    // tipping wings should lead to small changes in one of the axes G forces
    // as the axis becomes tipped toward the ground.
    // look for the change in direction,


    // - reject changes bigger than "allowable" (but change up to 'allowable' amount)
    // - average the results over a long period of time
    //     time period chosen so that a slow change can be detected in single sample
    //     if the change threshold is reached, do something (brightness?)

	now = millis();
	if (now - done_time < interval )
		return;
	done_time = now;

	// read the accelerometer
    accel.read (); // update the 3-axis from accelerometer

    // produce a signal that is integrated from the accelerometer output, in the 1/2 second
    //   rolloff range - this is used to measure changes in the Seagull attitude, side-to-side
    accel.filter();

    // produce a signal that is integrated from the accelerometer output, in the 5 second
    //   rolloff range - this produces a baseline of the attitude where the seagull sits at rest
    accel.integrate();

    // output the readings to the serial port for external analysis
    Serial.print((long) brightness);
    Serial.print(", ");

	Serial.print((long) (accel.x_filtered - accel.x_integrated) / Q10P21_ONE);
	Serial.println(" ");

    // short delay in between readings/
    delay (1);

    // check the difference between the changes of attitude and the baseline attitude
    //    and if they are different enough, then the wings are considered tipped.
    // Over time, the brightness is adjusted based on the tipping.

	#define MAX_BRIGHTNESS 250
    interval = 10;

    if(accel.x_filtered - accel.x_integrated > 30 * Q10P21_ONE)
    {
		if(brightness < MAX_BRIGHTNESS)
		{
			brightness+=4;
			FastLED.show(brightness);
		    interval = 30;
		}
    }
    else if(accel.x_filtered - accel.x_integrated < -30 * Q10P21_ONE)
    {
		if(brightness > 0)
		{
			brightness-=4;
			FastLED.show(brightness);
		    interval = 30;
		}
    }
}
