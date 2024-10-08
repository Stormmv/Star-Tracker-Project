#include "global.h"

// define motor and accelerometer
AccelStepper motor(AccelStepper::FULL4WIRE, 6, 8, 7, 9);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// for angle calculation
float x = 0.0;
float y = 0.0;
float z = 0.0;
float initialAngle = 0.0;

// motor controller
int acceleration = 20000;
int maxSpeed = 300;
float speed = 130;
int steps = 200;

bool debugPrint = true;

float kp = 0.95;
float ki = 0.2;
float kd = 0.1;

float lastAngle = 0.0;

float q = 0.02; // Process noise covariance
float r = 0.2; // Measurement noise covariance
float k = 0;     // Kalman gain
float x_hat = 0; // Estimated value
float p = 1;     // Error covariance
float kz;         // Measurement

//====================================================================================================

// get angle function
// gets the angle and averages it so that it is accurate enough to calibrate with
int averageTimes = 200;
float getAngle()
{
    // get average angle
    delay(1000); // to stop any vibrations or movements that may throw off the angle calculation
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

float getRawAngle()
{
    sensors_event_t event;
    accel.getEvent(&event);
    x = event.acceleration.x;
    y = event.acceleration.y;
    z = event.acceleration.z;
    return atan2(x, z) * (180.0 / M_PI);
}