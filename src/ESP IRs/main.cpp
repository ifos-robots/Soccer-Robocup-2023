//CLASSE PARA CALCULAR A MÉDIA DA MOVIMENTAÇÃO DO ROBÔ

#include "IR.h"

void setup() {
  Serial.begin(115200);

    //Sender 2

    sender2Serial.begin(9600, SERIAL_8N1, SENDER2_RX_PIN, SENDER2_TX_PIN);
    /*
    SERIAL_8N1: 
        8: 8 bits per byte
        N: No parity
        1: One stop bit
    */

  setIRPinsInput();
}

void loop() {
  float pulseWidth[IR_NUM];
  sensorInfo_t sensorInfo;
  vectorXY_t vectorXY;
  vectorRT_t vectorRT;
  vectorRT_t vectorRTWithSma;

  sensorInfo  = getSensorPulseWidth(pulseWidth, T_MODEA);
  vectorXY    = calcVectorXYFromPulseWidth(pulseWidth);
  vectorRT    = calcRTfromXY(&vectorXY);

  vectorRTWithSma.theta   = smaForTheta.updateData(vectorRT.theta);
  vectorRTWithSma.radius  = smaForRadius.updateData(vectorRT.radius);

  if (millis() - time_ms > 50) {
    time_ms = millis();

    serialPrintAllPusleWidth(pulseWidth, &sensorInfo);
    Serial.print("\t");
    serialPrintVectorXY(&vectorXY);
    Serial.print("\t");
    serialPrintVectorRT(&vectorRTWithSma);
    Serial.print("\t");
    Serial.print(millis());
    Serial.print("\n");
  }


    //Sender 2
    sender2Serial.print("[Infravermelhos];"+String(vectorRTWithSma.radius)+";"+String(vectorRTWithSma.theta));

}

//FUNÇÃO PARA PRINTAR AS LARGURAS DE PULSO DE CADA IR
void serialPrintAllPusleWidth(float *pulseWidth, sensorInfo_t *infop) {
  for(int i = 0; i < IR_NUM; i++) {
    Serial.print(pulseWidth[i]); 
    Serial.print("\t");
  }
  Serial.print(infop->activeSensors); 
  Serial.print("\t");
  Serial.print(infop->maxSensorNumber);
  Serial.print("\t");
  Serial.print(infop->maxPulseWidth); 
}

//FUNÇÃO PARA PRINTAR AS COORDENDAS XY
void serialPrintVectorXY(vectorXY_t *self) {
  Serial.print(self->x); 
  Serial.print("\t");
  Serial.print(self->y);
}

//FUNÇÃO PARA PRINTAR ANGULO E RAIO
void serialPrintVectorRT(vectorRT_t *self) {
  Serial.print(self->radius);
  Serial.print("\t");
  Serial.print(self->theta);
}

//CONSTRUÇÃO DO TAMANHO DA ARRAY E SUA QUANTIDADE DE DADOS
MovingAverage::MovingAverage(uint16_t num_array){
  dataArray = new float[num_array];
  sizeOfDataArray = num_array;
  count = 0;
}

//ATUALIZA OS VALORES DOS DADOS DA ARRAY E DEPOIS CALCULA SUA MÉDIA
float MovingAverage::updateData(float value){
  count++;
  if(count >= sizeOfDataArray) count = 0;
  dataArray[count] = value;

  float rslt = 0;
  for(int i = 0; i < sizeOfDataArray; ++i){
    rslt += dataArray[i];
  }
  return rslt/sizeOfDataArray;
}

//RESET DOS VALORES DA ARRAY PARA UM NOVO CÁLCULO
void MovingAverage::reset(){
  for(int i = 0; i < sizeOfDataArray; ++i){
    dataArray[i] = 0;
  }
}

//FUNÇÃO PARA INICIALIZAR OS PINOS DOS SENSORES COMO INPUT
void setIRPinsInput(){
  for(int i = 0; i < IR_NUM; ++i){
    pinMode(SensorPins[i], INPUT);
  }
}

//VERIFICAR O NÍVEL LÓGICO DE CADA PINO
bool getSensorPin(uint8_t pin) {
  return digitalRead(SensorPins[pin]) == LOW;
}

//FUNÇÃO PARA CALCULAR A LARGURA DE PULSO DE CADA IR
sensorInfo_t getSensorPulseWidth(float pulseWidth[IR_NUM], uint16_t timeLimit){
  sensorInfo_t sensorInfo;
  for(int i = 0; i < IR_NUM; i++){
    pulseWidth[i] = 0;
  }
  const unsigned long startTime_us = micros();
  do{
    for(int i = 0; i < IR_NUM; i++){
      if(getSensorPin(i) == false){
        pulseWidth[i] = deltaPulseWidth;
      }
    }
  } while((micros() - startTime_us) < timeLimit);

  sensorInfo.activeSensors = 0;
  sensorInfo.maxPulseWidth = 0;
  sensorInfo.maxSensorNumber = 0;
  for(int i = 0; i < IR_NUM; i++){
    if(pulseWidth[i] > 0){
      sensorInfo.activeSensors += 1;
    }
    if(pulseWidth[i] > sensorInfo.maxPulseWidth){
      sensorInfo.maxPulseWidth = pulseWidth[i];
      sensorInfo.maxSensorNumber = i;
    }
  }
  return sensorInfo;
}

//FUNÇÃO PARA CALCULAR AS COORDENADAS XY A PARTIR DA LARGURA DE PULSO
vectorXY_t calcVectorXYFromPulseWidth(float *pulseWidth) {
  vectorXY_t rslt = {0, 0};
  for(int i = 0; i < IR_NUM; i++) {
    rslt.x += pulseWidth[i] * unitVectorX[i];
    rslt.y += pulseWidth[i] * unitVectorY[i];
  }
  return rslt;
}

//FUNÇÃO PARA CALCULAR O ANGULO E RAIO A PARTIR DE XY
vectorRT_t calcRTfromXY(vectorXY_t *vectorXY_p) {
  vectorRT_t rslt;
  rslt.radius  = sqrt(pow(vectorXY_p->x, 2.0) + pow(vectorXY_p->y, 2.0));
  rslt.theta   = atan2(vectorXY_p->x, vectorXY_p->y) / PI * 180.0;
  return rslt;
}
