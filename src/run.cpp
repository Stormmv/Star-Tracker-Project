#include "run.h"

float finalAngle = 7.5; // Target final angle (degrees) at 30 minutes
float debugAngle = 0.0;

float previousError = 0.0;
float integral = 0.0;
unsigned long lastTime = 0;
unsigned long lastPIDTime = 0; // Track the last time the PID loop ran
unsigned long lastDebugTime = 0;
float setPoint = 0.0;

void run()
{
    unsigned long currentTime = millis();

    // run motor for 30 minutes

    if (currentTime - lastPIDTime >= 10) // Check if 10ms have passed
    {
        // Calculate the dynamic setPoint: the target angle at the current time
        float elapsedTime = currentTime / 1000.0;       // Convert time to seconds
        setPoint = (elapsedTime / 1800.0) * finalAngle; // Target angle at this time

        // Get the current angle with filtering
        kz = getRawAngle(); // Replace with your function to get the current angle measurement

        // Prediction step
        p = p + q; // Update error covariance

        // Update step
        k = p / (p + r);                  // Calculate Kalman gain
        x_hat = x_hat + k * (kz - x_hat); // Update estimated value
        p = (1 - k) * p;                  // Update error covariance

        // Now, use x_hat instead of currentAngle in your calculations
        //float currentAngle = (lastAngle * 0.9) + (x_hat * 0.1); // Use the filtered angle
        //lastAngle = currentAngle;
        float currentAngle = x_hat;

        // Calculate error
        float error = setPoint - (currentAngle - initialAngle);

        // Calculate integral and derivative
        integral += error * (currentTime - lastPIDTime);
        float derivative = (error - previousError) / (currentTime - lastPIDTime);

        // Calculate PID output
        float speed = kp * error + ki * integral + kd * derivative;

        // Set motor speed based on PID output (adjust according to your motor's capabilities)
        motor.setSpeed(speed); // Assuming motor.setSpeed() adjusts speed appropriately

        // Run the motor at the calculated speed

        // Update for the next loop
        previousError = error;
        lastPIDTime = currentTime; // Update the time for the next PID loop
        if (debugPrint)
        {
            if (currentTime - lastDebugTime >= 60000) // Every 60 seconds (1 minute)
            {
                debugAngle = getAngle();
                Serial.print("Time: ");
                Serial.print(currentTime / 60000); // Print time in minutes
                Serial.print(" min | Current Angle Change: ");
                Serial.print(debugAngle - initialAngle);
                Serial.print(" | Desired Angle Change: ");
                Serial.println(setPoint);
                lastDebugTime = currentTime;
            }
        }
    }

    if (motor.speed() < 10)
    {
        motor.setSpeed(10);
    }

    motor.runSpeed();

    // get final angle and print it once 30 minutes is up, then stop
    if (millis() >= 1800000)
    {
        debugAngle = getAngle();
        Serial.print("Time: ");
        Serial.print(currentTime / 60000); // Print time in minutes
        Serial.print(" min | Current Angle Change: ");
        Serial.print(debugAngle - initialAngle);
        Serial.print(" | Desired Angle Change: ");
        Serial.println(setPoint);

        // Stop the motor
        motor.stop();

        while (1)
        {
        } // End program
    }
}