#ifndef HANDLELINE_H
#define HANDLELINE_H

#include <Arduino.h>
#include "Adafruit_TCS34725.h"

uint16_t r1, g1, b1, c1;
uint16_t r2, g2, b2, c2;
uint16_t r3, g3, b3, c3;

#define WHITE_COLOR_THRESHOLD 200


Adafruit_TCS34725 tcs1;
Adafruit_TCS34725 tcs2;
Adafruit_TCS34725 tcs3;

bool s1; bool s2; bool s3;
enum LineState { NONE, LEFT, RIGHT, FRONT, BACK };
void correctRobotDirection(LineState lineState);
LineState checkLineState();
bool checkSensor(uint16_t r, uint16_t g, uint16_t b);
void TCA9548A(uint8_t bus);


#endif