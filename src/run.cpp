#include "run.h"

float finalAngle = 7.5; // Target final angle (degrees) at 30 minutes
float debugAngle = 0.0;
unsigned long lastTime = 0;
unsigned long lastDebugTime = 0;

void run()
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime / 1000; // Convert time to seconds

    // Kalman filter update
    kz = getRawAngle(); // Get raw sensor angle
    p = p + q;
    float k = p / (p + r);
    x_hat = x_hat + k * (kz - x_hat);
    p = (1 - k) * p;

    // Calculate the expected angle based on time
    float totalTime = 1800.0;                                     // Total time in seconds (30 minutes)
    float expectedAngle = (elapsedTime / totalTime) * finalAngle; // Linearly scale the angle with time

    // Calculate the current angle using Kalman filtered data
    float currentAngle = x_hat;

    // Compare current angle with expected angle and adjust motor speed
    float angleDifference = expectedAngle - (currentAngle - initialAngle);

    // Speed adjustment based on angle difference
    speed = speed * (angleDifference + 1);

    // Cap the speed between minimum and maximum values
    if (speed < minSpeed)
    {
        speed = minSpeed; // Minimum speed
    }
    if (speed > maxSpeed)
    {
        speed = maxSpeed; // Cap at maximum speed
    }
    motor.setSpeed(speed);
    motor.runSpeed();

    // Debug printing every 60 seconds
    if (currentTime - lastDebugTime >= 60000) // Every 60 seconds (1 minute)
    {
        debugAngle = getAngle();
        Serial.print("Time: ");
        Serial.print(currentTime / 60000); // Print time in minutes
        Serial.print(" min | Current Angle Change: ");
        Serial.print(debugAngle - initialAngle);
        Serial.print(" | Desired Angle Change: ");
        Serial.print((elapsedTime / totalTime) * finalAngle);
        Serial.print(" | Kalman Angle: ");
        Serial.print(x_hat);
        Serial.print(" | Actual Angle: ");
        Serial.println(debugAngle);
        lastDebugTime = currentTime;
    }

    // Stop the motor when 30 minutes (1800000 ms) have passed
    if (millis() >= 1800000)
    {
        motor.stop();
        debugAngle = getAngle();
        Serial.print("Time: 30 min");
        Serial.print(" | Current Angle Change: ");
        Serial.print(currentAngle - initialAngle);
        Serial.print(" | Desired Angle Change: ");
        Serial.print(finalAngle);
        Serial.print(" | Kalman Angle: ");
        Serial.print(x_hat);
        Serial.print(" | Actual Angle: ");
        Serial.println(debugAngle);
        while (1)
        {
        } // End program
    }
}
