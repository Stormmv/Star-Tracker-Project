#include "run.h"

void run()
{
    //run motor for 30 minutes
    if (millis() < 1800000)
    {
        motor.runSpeed();
    }

    //get final angle and print it once 30 minutes is up, then stop
    if (millis() >= 1800000)
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