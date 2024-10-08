#include "run.h"

float kp = 1.0;  // Proportional constant
float ki = 0.1;  // Integral constant
float kd = 0.05; // Derivative constant

float finalAngle = 7.5; // Target final angle (degrees) at 30 minutes
float lastAngle = 0.0;  // Initialize this based on the actual start angle

float previousError = 0.0;
float integral = 0.0;
unsigned long lastTime = 0;

void run()
{
    unsigned long currentTime = millis();
    unsigned long timeChange = currentTime - lastTime;
    // run motor for 30 minutes

    if (millis() < 1800000)
    {
        // Calculate the dynamic setPoint: the target angle at the current time
        float elapsedTime = currentTime / 1000.0;             // Convert time to seconds
        float setPoint = (elapsedTime / 1800.0) * finalAngle; // Target angle at this time

        // Get the current angle
        float currentAngle = (lastAngle * 0.9) + (getRawAngle() * 0.1);

        // Calculate error
        float error = setPoint - (currentAngle - initialAngle);

        // Calculate integral and derivative
        integral += error * timeChange;
        float derivative = (error - previousError) / timeChange;

        // Calculate PID output
        float output = kp * error + ki * integral + kd * derivative;

        // Set motor speed based on PID output (adjust according to your motor's capabilities)
        motor.setSpeed(output); // Assuming motor.setSpeed() adjusts speed appropriately

        // Run the motor at the calculated speed
        motor.runSpeed();

        // Update for the next loop
        previousError = error;
        lastTime = currentTime;
    }

    // get final angle and print it once 30 minutes is up, then stop
    if (millis() >= 1800000)
    {
        float currentAngle = getAngle();
        float angleChange = currentAngle - initialAngle;
        Serial.print("Final angle: ");
        Serial.println(currentAngle);
        Serial.print("Angle change: ");
        Serial.println(angleChange);
        Serial.print("Expected angle change: 7.5");

        // Stop the motor
        motor.stop();

        while (1)
        {
        } // End program
    }
}