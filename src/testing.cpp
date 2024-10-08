#include "testing.h"

// array to store angles for each minute
float angleChanges[15];

// time in milliseconds
unsigned long previousMillis = 0;

// counter for minutes
int minuteCounter = 0;

// starting speed for calibration
int startingSpeed = speed;

void testLogFor15m()
{
    // run motor for 15 minutes
    unsigned long currentMillis = millis();
    if (currentMillis < 900000)
    {
        motor.runSpeed();
    }

    // get angle change every minute
    if (currentMillis - previousMillis >= 60000 && minuteCounter < 15)
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

    // print final angle changes after 15 minutes
    if (currentMillis >= 900000 && minuteCounter == 15)
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

// calibrate motor speed
void testGetSpeed()
{
    // run motor for 2 minutes
    motor.setSpeed(startingSpeed);
    motor.runSpeed();
    // get angle change every 2 minutes
    if (millis() - previousMillis >= 120000)
    {
        float currentAngle = getAngle();
        float angleChange = currentAngle - initialAngle;
        Serial.print("Current angle: ");
        Serial.println(currentAngle);
        Serial.print("Angle change: ");
        Serial.println(angleChange);

        // increase speed if angle change is less than 0.49
        if (angleChange < 0.49)
        {
            startingSpeed++;
            Serial.print("Speed increased to: ");
            Serial.println(startingSpeed);
            Serial.println("==============================================");
        }

        // decrease speed if angle change is more than 0.51
        else if (angleChange > 0.51)
        {
            startingSpeed--;
            Serial.print("Speed decreased to: ");
            Serial.println(startingSpeed);
            Serial.println("==============================================");
        }

        // print speed if angle change is between 0.49 and 0.51
        else if (angleChange >= 0.49 && angleChange <= 0.51)
        {
            delay(50);
            Serial.print("Motor Speed Fine:");
            Serial.println(startingSpeed);
            Serial.println("==============================================");
        }

        // reset angle and time
        initialAngle = currentAngle;
        previousMillis = millis();
    }
}

// show angle for accelerometer testing
void showAngle()
{
    float currentAngle = getAngle();
    Serial.print("Current angle: ");
    Serial.println(currentAngle);
}

// test Kalman filter
void testKalmanFilter()
{
    kz = getRawAngle(); // Replace with your function to get the current angle measurement

    // Prediction step
    p = p + q; // Update error covariance

    // Update step
    k = p / (p + r);                  // Calculate Kalman gain
    x_hat = x_hat + k * (kz - x_hat); // Update estimated value
    p = (1 - k) * p;                  // Update error covariance

    // Now, use x_hat instead of currentAngle in your calculations
    float currentAngle = (lastAngle * 0.9) + (x_hat * 0.1); // Use the filtered angle
    lastAngle = currentAngle;
    Serial.print("Current angle: ");
    Serial.println(currentAngle);
}
