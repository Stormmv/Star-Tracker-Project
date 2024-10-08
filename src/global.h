#pragma once

#include <AccelStepper.h>
#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

extern AccelStepper motor;
extern Adafruit_ADXL345_Unified accel;

extern float x;
extern float y;
extern float z;
extern float initialAngle;

extern int acceleration;
extern int maxSpeed;
extern float speed;
extern int steps;

extern bool debugPrint;

extern float kp;
extern float ki;
extern float kd;

float getAngle();
float getRawAngle();
