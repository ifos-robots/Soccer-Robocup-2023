#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <NewPing.h>
#include <MPU9250.h>
#include <Arduino.h>
#include <HardwareSerial.h>
          
//Ultrassonic Variables
#define TRIGGER_PIN  27
#define TRIGGER_PIN_1  14
#define TRIGGER_PIN_2  23
#define TRIGGER_PIN_3  18

#define ECHO_PIN    33
#define ECHO_PIN_1  25
#define ECHO_PIN_2  19
#define ECHO_PIN_3   4

#define MAX_DISTANCE_X 242
#define MAX_DISTANCE_Y 183

#define SENDER1_TX_PIN 17
#define SENDER1_RX_PIN 16 

#define R 11
extern float x;
extern float y;

float distances[4];

//MPU Variables
HardwareSerial sender1Serial(2); // UART2



#endif