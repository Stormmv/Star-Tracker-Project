#include "global.h"
#include "testing.h"
#include "run.h"

bool test15m = false;
bool test1m = false;
bool testLog15m = false;
bool testGetSpeedBool = false;
bool showAngleBool = false;

void setup()
{
  Serial.begin(115200);
  motor.setAcceleration(acceleration);
  motor.setMaxSpeed(maxSpeed);
  motor.setSpeed(speed);
  motor.setCurrentPosition(0);
  while (!accel.begin())
  {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    delay(500);
  }
  accel.setRange(ADXL345_RANGE_2_G);

  sensors_event_t event;
  accel.getEvent(&event);

  x = event.acceleration.x;
  y = event.acceleration.y;
  z = event.acceleration.z;
  initialAngle = getAngle();
  Serial.print("Starting angle: ");
  Serial.println(initialAngle);

  motor.setSpeed(speed);
}

void loop()
{
  if (test15m)
  {
    test15min();
  }
  else if (test1m)
  {
    test1min();
  }
  else if (testLog15m)
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