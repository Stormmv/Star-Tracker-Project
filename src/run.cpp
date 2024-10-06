#include "run.h"

int timeToRun = Minute1 * 30;

void run()
{
    if (millis() < timeToRun)
    {
        motor.runSpeed();
    }
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