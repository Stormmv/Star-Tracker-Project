#include "testing.h"

float angleChanges[15];
unsigned long previousMillis = 0;
int minuteCounter = 0;
int startingSpeed = 144;

void test15min()
{
    if (millis() < (Minute1 * 15))
    {
        motor.runSpeed();
    }
    if (millis() >= (Minute1 * 15))
    {
        float currentAngle = getAngle();
        float angleChange = currentAngle - initialAngle;
        Serial.print("Final angle: ");
        Serial.println(currentAngle);
        Serial.print("Angle change: ");
        Serial.println(angleChange);
        Serial.print("Expected angle change: 3.75");
        while (1)
        {
        }
    }
}

void test1min()
{
    if (millis() < Minute1)
    {
        motor.runSpeed();
    }
    if (millis() >= Minute1)
    {
        float currentAngle = getAngle();
        float angleChange = currentAngle - initialAngle;
        Serial.print("Final angle: ");
        Serial.println(currentAngle);
        Serial.print("Angle change: ");
        Serial.println(angleChange);
        Serial.print("Expected angle change: 0.25");
        while (1)
        {
        }
    }
}

void testLogFor15m()
{
    unsigned long currentMillis = millis();
    if (currentMillis < (Minute1 * 15))
    {
        motor.runSpeed();
    }

    if (currentMillis - previousMillis >= Minute1 && minuteCounter < 15)
    {
        previousMillis = currentMillis;

        float currentAngle = getAngle();
        float angleChange = currentAngle - initialAngle;

        angleChanges[minuteCounter] = angleChange;
        Serial.print("Minute ");
        Serial.print(minuteCounter + 1);
        Serial.print(": Angle change = ");
        Serial.println(angleChange);
        float expectedAngleChange2 = 0.25 * (minuteCounter + 1);
        Serial.print("Expected angle change: ");
        Serial.println(expectedAngleChange2);
        Serial.print("current angle: ");
        Serial.println(currentAngle);
        Serial.println("==============================================");

        minuteCounter++;
    }

    if (currentMillis >= (Minute1 * 15) && minuteCounter == 15)
    {
        Serial.println("Final angle changes over 15 minutes:");
        for (int i = 0; i < 15; i++)
        {
            Serial.println("==============================================");
            Serial.print("Minute ");
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.println(angleChanges[i]);
            float expectedAngleChange = 0.25 * (i + 1);
            Serial.print("Expected angle change: ");
            Serial.println(expectedAngleChange);
        }

        while (1)
        {
        }
    }
}

void testGetSpeed()
{
    motor.setSpeed(startingSpeed);
    motor.runSpeed();
    if (millis() - previousMillis >= (Minute1 * 2))
    {
        float currentAngle = getAngle();
        float angleChange = currentAngle - initialAngle;
        Serial.print("Current angle: ");
        Serial.println(currentAngle);
        Serial.print("Angle change: ");
        Serial.println(angleChange);
        if (angleChange < 0.49)
        {
            startingSpeed++;
            Serial.print("Speed increased to: ");
            Serial.println(startingSpeed);
            Serial.println("==============================================");
        }
        else if (angleChange > 0.51)
        {
            startingSpeed--;
            Serial.print("Speed decreased to: ");
            Serial.println(startingSpeed);
            Serial.println("==============================================");
        }
        else if (angleChange >= 0.49 && angleChange <= 0.51)
        {
            delay(50);
            Serial.print("Motor Speed Fine:");
            Serial.println(startingSpeed);
            Serial.println("==============================================");
        }
        initialAngle = currentAngle;
        previousMillis = millis();
    }
}

void showAngle()
{
    float currentAngle = getAngle();
    Serial.print("Current angle: ");
    Serial.println(currentAngle);
}
