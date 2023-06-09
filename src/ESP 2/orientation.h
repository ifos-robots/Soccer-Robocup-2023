#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "Ultrasonic.h"
#include "MPU9250.h"
#include <Arduino.h>
#include <HardwareSerial.h>
          
//Ultrassonic Variables
#define R 11
float x, y;
float distances[4];

struct UltrasonicSensor { 
  Ultrasonic ultrasonic;
  float x;
  float y;
};

//Ultrassonic and Variables
UltrasonicSensor sensors[] = {
  { Ultrasonic(27, 14), 0, R },    // Sensor North
  { Ultrasonic(14, 0), 0, -R },    // Sensor South
  { Ultrasonic(25, 26), R, 0 },    // Sensor East/Right
  { Ultrasonic(32, 33), -R, 0 },   // Sensor West/Left
};

//MPU Variables
HardwareSerial sender1Serial(2); // UART2
#define SENDER1_TX_PIN 17
#define SENDER1_RX_PIN 16

MPU9250 mpu; 


#endif