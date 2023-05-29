#ifndef IR_H
#define IR_H

#include <Arduino.h>


// Sender 2
HardwareSerial sender2Serial(1); // UART1
#define SENDER2_TX_PIN 4
#define SENDER2_RX_PIN 5


class MovingAverage{
  private:
    float* dataArray;
    uint16_t sizeOfDataArray;
    uint16_t count;
  public:
    MovingAverage(uint16_t num_array);
    float updateData(float value);
    void reset();
};

//DEFINIÇÃO DE ANGULO E RAIO
MovingAverage smaForRadius(20);
MovingAverage smaForTheta(20);

//VARIÁVEIS GERAIS
#define IR_NUM 12
#define deltaPulseWidth 2.0
#define PI 3.14159265359
unsigned long time_ms = 0;
#define T_MODEA 833

//DEFINIÇOES DE PINOS PARA OS IRS
const uint8_t SensorPins[IR_NUM]  = {5, 6, 7, 8, 4, 2, 3, 17, 12, 11, 10, 9};

//COORDENADAS DOS IRS
const float unitVectorX[IR_NUM] = {0.000, 0.500, 0.866, 1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500};
const float unitVectorY[IR_NUM] = {1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500, 0.000, 0.500, 0.866};

//ESTRUTURAS PARA SENSORES E VETORES
struct sensorInfo_t{
  int activeSensors;
  int maxPulseWidth;
  int maxSensorNumber;
};

struct vectorXY_t{
  float x;
  float y;
};

struct vectorRT_t{
  float radius;
  float theta;
};

void setIRPinsInput(void);
bool getSensorPin(uint8_t pin);
sensorInfo_t getSensorPulseWidth(float pulseWidth[IR_NUM], uint16_t timeLimit);
vectorXY_t calcVectorXYFromPulseWidth(float *pulseWidth);
vectorRT_t calcRTfromXY(vectorXY_t *vectorXY_p);


#endif