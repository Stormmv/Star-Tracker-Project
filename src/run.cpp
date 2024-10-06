#include "run.h"

int timeToRun = Minute1 * 30;

void run()
{
    //run motor for 30 minutes
    if (millis() < timeToRun)
    {
        motor.runSpeed();
    }

    //get final angle and print it once 30 minutes is up, then stop
    if (millis() >= timeToRun)
    {
        float currentAngle = getAngle();
        float angleChange = currentAngle - initialAngle;
        Serial.print("Final angle: ");
        Serial.println(currentAngle);
        Serial.print("Angle change: ");
        Serial.println(angleChange);
        Serial.print("Expected angle change: 7.5");
        while (1)
        {
        }
    }
}