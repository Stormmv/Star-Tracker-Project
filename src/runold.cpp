// #include "run.h"

// float debugAngle1 = 0.0;

// float previousError = 0.0;
// float integral = 0.0;
// unsigned long lastTime = 0;
// unsigned long lastPIDTime = 0; // Track the last time the PID loop ran
// unsigned long lastDebugTime = 0;
// float setPoint = 0.0;

// void run()
// {
//     unsigned long currentTime = millis();

//     kz = getRawAngle();
//     p = p + q;
//     k = p / (p + r);
//     x_hat = x_hat + k * (kz - x_hat);
//     p = (1 - k) * p;

//     if (currentTime - lastPIDTime >= 10) // Check if 10ms have passed
//     {
//         // Calculate the dynamic setPoint: the target angle at the current time
//         float elapsedTime = currentTime / 1000.0;       // Convert time to seconds
//         setPoint = (elapsedTime / 1800.0) * 7.5; // Target angle at this time

//         float currentAngle = x_hat;

//         // Calculate error
//         float error = setPoint - (currentAngle - initialAngle);

//         // Calculate integral and derivative
//         integral += error * (currentTime - lastPIDTime);
//         float derivative = (error - previousError) / (currentTime - lastPIDTime);

//         // Calculate PID output
//         speed = kp * error + ki * integral + kd * derivative;

//         if (speed > maxSpeed)
//         {
//             speed = maxSpeed;
//         } else if (speed < 10)
//         {
//             speed = 10;
//         }
//         // set motor speed
//         motor.setSpeed(speed);

//         // Run the motor at the calculated speed

//         // Update for the next loop
//         previousError = error;
//         lastPIDTime = currentTime; // Update the time for the next PID loop
//         if (debugPrint)
//         {
//             if (currentTime - lastDebugTime >= 60000) // Every 60 seconds (1 minute)
//             {
//                 debugAngle1 = getAngle();
//                 Serial.print("Time: ");
//                 Serial.print(currentTime / 60000); // Print time in minutes
//                 Serial.print(" min | Current Angle Change: ");
//                 Serial.print(debugAngle1 - initialAngle);
//                 Serial.print(" | Desired Angle Change: ");
//                 Serial.print(setPoint);
//                 Serial.print(" | Kalman Angle: ");
//                 Serial.print(x_hat);
//                 Serial.print(" | Actual Angle: ");
//                 Serial.println(getAngle());
//                 lastDebugTime = currentTime;
//             }
//         }
//     }

//     if (speed < 10)
//     {
//         motor.setSpeed(10);
//     }
//     else
//     {
//         motor.setSpeed(speed);
//     }
//     motor.runSpeed();

//     // get final angle and print it once 30 minutes is up, then stop
//     if (millis() >= 1800000)
//     {
//         debugAngle1 = getAngle();
//         Serial.print("Time: ");
//         Serial.print(currentTime / 60000); // Print time in minutes
//         Serial.print(" min | Current Angle Change: ");
//         Serial.print(debugAngle1 - initialAngle);
//         Serial.print(" | Desired Angle Change: ");
//         Serial.println(setPoint);

//         // Stop the motor
//         motor.stop();

//         while (1)
//         {
//         } // End program
//     }
// }