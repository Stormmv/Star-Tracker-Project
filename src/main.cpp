#include "global.h"
#include "testing.h"
#include "run.h"

// testing booleans
bool testLog15m = false;
bool testGetSpeedBool = false;
bool showAngleBool = false;
bool testKalmanFilterBool = false;

void setup()
{
  Serial.begin(115200);
  // set up motor
  motor.setAcceleration(acceleration);
  motor.setMaxSpeed(maxSpeed);

  // set up accelerometer
  while (!accel.begin())
  {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    delay(500);
  }
  accel.setRange(ADXL345_RANGE_2_G);

  // get initial angle and print it
  initialAngle = getAngle();
  lastAngle = initialAngle;
  if (debugPrint)
  {
    Serial.print("Starting angle: ");
    Serial.println(initialAngle);
  }
}

void loop()
{
  if (testLog15m)
  {
    testLogFor15m();
  }
  else if (testGetSpeedBool)
  {
    testGetSpeed();
  }
  else if (showAngleBool)
  {
    showAngle();
  }
  else if (testKalmanFilterBool)
  {
    testKalmanFilter();
  }
  else
  {
    run();
  }
}