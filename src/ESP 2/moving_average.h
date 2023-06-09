

#include <Arduino.h>
#ifndef __MOVING_AVERAGE__
#define __MOVING_AVERAGE__

class MovingAverage {

/*
    The purpose of using the MovingAverage class in the code is to apply the moving average algorithm to smooth out variations in the vectorRT.theta and vectorRT.radius values over a window of 20 data points. By updating the moving average with new values over time, it provides a filtered or smoothed representation of the data, which can be useful for reducing noise or fluctuations in the measurements.
*/

private:
    float *dataArray;
    uint16_t sizeOfDataArray;
    uint16_t count;
public:
    MovingAverage(uint16_t num_array);
    float updateData(float value);
    void reset(void);
};

MovingAverage::MovingAverage(uint16_t num_array) {
    dataArray = new float[num_array];
    sizeOfDataArray = num_array;
    count = 0;
}

float MovingAverage::updateData(float value) {
    count++;
    if (count >= sizeOfDataArray) count = 0;
    dataArray[count] = value;
 
    float rslt = 0;
    for (int i = 0; i < sizeOfDataArray; ++i) {
        rslt += dataArray[i];
    }
    
    return rslt / sizeOfDataArray;
}

void MovingAverage::reset(void) {
    for (int i = 0; i < sizeOfDataArray; ++i) {
        dataArray[i] = 0;
    }
}

#endif