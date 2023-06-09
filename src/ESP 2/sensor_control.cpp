#include "sensor_control.h"
#include <Arduino.h>




void setAllSensorPinsInput(void) {
    for (int i = 0; i < IR_NUM; ++i) {
        pinMode(SensorPins[i], INPUT);
    }
}

/*
 Port manipulation for faster digital input reading.
 For more details, refer to the following link:
 http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=849

 Since it's not generalized with digitalRead(), this is a hardware-dependent implementation.
     if(digitalRead(SensorPins[pin]) == HIGH) {
        return true;
    } else {
        return false;
    }
    */

bool getSensorPin(uint8_t pin) {
    return true ? digitalRead(SensorPins[pin]) == HIGH : false;
}

sensorInfo_t getAllSensorPulseWidth(int pulseWidth[IR_NUM], uint16_t timeLimit) {
    // Structure to store experimental data
    sensorInfo_t sensorInfo;

    // Initialize pulseWidth[] as an accumulation variable
    for(int i = 0; i < IR_NUM; i++) {
        pulseWidth[i] = 0;
    }

    // Do the sensor reading while monitoring time (833us) with a do-while loop
    const unsigned long startTime_us = micros();
    do {
        for (int i = 0; i < IR_NUM; i++) {
            if(getSensorPin(i) == false) {
                //pulseWidth[i] += deltaPulseWidth;
                pulseWidth[i] = micros() - startTime_us;
            }
        }
    } while((micros() - startTime_us) < timeLimit);

    // If you only want to perform sensing through vector calculations, the following implementation is unnecessary
    sensorInfo.activeSensors    = 0; // Number of sensors responding to the ball
    sensorInfo.maxPulseWidth    = 0; // Pulse width of the sensor with the strongest response
    sensorInfo.maxSensorNumber  = 0; // Number of the sensor with the strongest response
    for(int i = 0; i < IR_NUM; i++) {
        if(pulseWidth[i] > 0) {
            sensorInfo.activeSensors += 1;
        }
        if(pulseWidth[i] > sensorInfo.maxPulseWidth) {
            sensorInfo.maxPulseWidth = pulseWidth[i];
            sensorInfo.maxSensorNumber = i;
        }
    }

    return sensorInfo;
}

vectorXY_t calcVectorXYFromPulseWidth(float *pulseWidth) {
    vectorXY_t rslt = {0, 0};
    for(int i = 0; i < IR_NUM; i++) {
        rslt.x += pulseWidth[i] * unitVectorX[i];
        rslt.y += pulseWidth[i] * unitVectorY[i];
    }

    return rslt;
}

vectorRT_t calcRTfromXY(vectorXY_t *vectorXY_p) {
    vectorRT_t rslt;
    rslt.radius  = sqrt(pow(vectorXY_p->x, 2.0) + pow(vectorXY_p->y, 2.0));
    rslt.theta   = atan2(vectorXY_p->x, vectorXY_p->y) / PI * 180.0;
    return rslt;
}
