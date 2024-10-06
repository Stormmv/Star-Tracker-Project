#include "global.h"

//define motor and accelerometer
AccelStepper motor(AccelStepper::FULL4WIRE, 10, 12, 11, 13);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

//for angle calculation
float x = 0.0;
float y = 0.0;
float z = 0.0;
float initialAngle = 0.0;

//motor controller
int acceleration = 20000;
int maxSpeed = 200;
int speed = 144;
int steps = 200;

//====================================================================================================

//get angle function
//gets the angle and averages it so that it is accurate enough to calibrate with
int averageTimes = 10000;
float getAngle()
{
    // get average angle
    delay(1000);
    sensors_event_t event;
    accel.getEvent(&event);
    float angleBefore = 0;

    for (int i = 0; i < averageTimes; i++)
    {
        accel.getEvent(&event);
        x = event.acceleration.x;
        y = event.acceleration.y;
        z = event.acceleration.z;
        angleBefore += atan2(x, z) * (180.0 / M_PI);
    }
    angleBefore /= averageTimes;
    return angleBefore;
}