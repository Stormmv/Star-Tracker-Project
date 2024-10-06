#include "global.h"
#include "testing.h"
#include "run.h"

//testing booleans
bool testLog15m = false;
bool testGetSpeedBool = false;
bool showAngleBool = false;

void setup()
{
  Serial.begin(115200);
  
  //set up motor
  motor.setAcceleration(acceleration);
  motor.setMaxSpeed(maxSpeed);
  motor.setSpeed(speed);
  motor.setCurrentPosition(0);

  //set up accelerometer
  while (!accel.begin())
  {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    delay(500);
  }
  accel.setRange(ADXL345_RANGE_2_G);

  //get initial angle and print it
  initialAngle = getAngle();
  Serial.print("Starting angle: ");
  Serial.println(initialAngle);

  //set up motor speed
  motor.setSpeed(speed);
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
  else
  {
    run();
  }
}