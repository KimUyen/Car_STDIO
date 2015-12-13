#ifndef __DEFINE_H__
#define __DEFINE_H__

/// ==========================================================
/// INCLUDE NECESSARY LIBRARY
/// ==========================================================
#include "Arduino.h"
#include <EEPROM.h>

const uint8_t gAddressEEPROM = 0;

/// ==========================================================
/// DEFINE SOMETHINGS FOR OBJECT DRIVER
/// ==========================================================
//  Motor RIGHT
#define EN_RIGHT    13
#define IN1_RIGHT   6
#define IN2_RIGHT   11
//  Motor LEFT
#define EN_LEFT     7
#define IN1_LEFT    10
#define IN2_LEFT    5
#define PWM         200

/// ==========================================================
/// DEFINE SOMETHINGS FOR OBJECT EYE
/// ==========================================================
// 1. Sensor SRF-05
#define TRIG_PIN    8
#define ECHO_PIN    12
#define DISTANCE_HAVE_OBSTACLE 30
#define DISTANCE_CAN_GO 50
// 2. Sensor IR
#define PHOTODIOT_IR  4
// 3. Servo
#define SERVO_PIN   9
#define ANGLE_0     0
#define ANGLE_90    90
#define ANGLE_180   180

/// ==========================================================
/// DEFINE SOMETHINGS FOR ENCODER USING IN DRIVER AND REGULATOR
/// ==========================================================
#define PULSESPERTURN   15
#define ENCODER_LEFT    2
#define ENCODER_RIGHT   3
#define HOLES_FOR_TURN  10
#define HOLES_DISC      15


/// ==========================================================
/// DEFINE ENUM
/// ==========================================================
typedef enum
{
  LEFT = 0,
  RIGHT = 1
}Wheel;

typedef enum
{
  L = 0,
  R = 1,
  CENTER
}Direct;

#endif
