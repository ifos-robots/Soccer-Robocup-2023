#ifndef __SENSOR_CONTROL__
#define __SENSOR_CONTROL__

#include "Arduino.h"
#define IR_NUM 12

// Hardware-dependent variables
const uint8_t   SensorPins[IR_NUM]  = {34, 35, 32, 33, 25, 26, 27, 14, 12, 13, 15, 2};
const float     unitVectorX[IR_NUM] = {0.000, 0.500, 0.866, 1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500};
const float     unitVectorY[IR_NUM] = {1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500, 0.000, 0.500, 0.866};
const float     deltaPulseWidth     = 2.0;

typedef struct {
    int activeSensors;      // Number of active sensors
    int maxPulseWidth;      // Maximum sensor value
    int maxSensorNumber;    // Number of the sensor with the maximum value
} sensorInfo_t;

typedef struct {
    float x;
    float y;
} vectorXY_t;

typedef struct {
    float radius;
    float theta;
} vectorRT_t;

void setAllSensorPinsInput(void);
bool getSensorPin(uint8_t pin);
sensorInfo_t getAllSensorPulseWidth(float pulseWidth[IR_NUM], uint16_t timeLimit);
vectorXY_t calcVectorXYFromPulseWidth(float *pulseWidth);
vectorRT_t calcRTfromXY(vectorXY_t *vectorXY_p);

#endif
