//CLASSE PARA CALCULAR A MÉDIA DA MOVIMENTAÇÃO DO ROBÔ
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

void setup() {
  Serial.begin(115200);
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
