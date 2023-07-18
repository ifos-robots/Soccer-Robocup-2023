
#include <Arduino.h>
#include "Motor.h"
#include "handleLine.h"

uint16_t r1, g1, b1, c1;
uint16_t r2, g2, b2, c2;
uint16_t r3, g3, b3, c3;

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

    return LineState::NONE;

}

//Check if a sensor is detecting a line (white color)
bool checkSensor(uint16_t r, uint16_t g, uint16_t b) {
    return (r > 200 && g > 200 && b > 200);
}
