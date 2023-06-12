
#include <Arduino.h>
#include "Motor.h"
#include "handleLine.h"






/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_540MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_540MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_540MS, TCS34725_GAIN_1X);


// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}


void correctRobotDirection(LineState lineState) {
    switch (lineState) {
        case NONE:
            // No line detected, no correction needed
            break;
        case LEFT:
            // Move robot to the right
            moveRobot(1, 0);
            break;
        case RIGHT:
            // Move robot to the left
            moveRobot(-1, 0);
            break;
        case FRONT:
            // Move robot backwards
            moveRobot(-1, 0);
            break;
        case BACK:
            // Move robot forward
            moveRobot(1, 0);
            break;
        default:
            // Invalid state, handle the error appropriately
            break;
    }
}

LineState checkLineState() {
    s1 = checkSensor(r1, g1, b1);
    s2 = checkSensor(r2, g2, b2);
    s3 = checkSensor(r3, g3, b3);

    if (s1 && !s2 && !s3){
        return LineState::FRONT;
    }
    else if (s2 && !s3 || s2 && s1 ){
        return LineState::RIGHT;
    }
    else if (s3 && !s2 || s1 && s3){
        return LineState::LEFT;
    }
    else if (s3 && s2){
        return LineState::BACK;
    }
}

//Check if a sensor is detecting a line (white color)
bool checkSensor(uint16_t r, uint16_t g, uint16_t b) {
    return (r > 200 && g > 200 && b > 200);
}
