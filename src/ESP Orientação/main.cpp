//BIBLIOTECAS
#include <Ultrasonic.h>

//VARIÁVEIS GERAIS
#define R 11
float x, y;
float distances[4];

struct UltrasonicSensor {
  Ultrasonic ultrasonic;
  float x;
  float y;
};

//DEFINIÇÃO DE SENSORES ULTRASSONICOS E SUAS VARIÁVEIS
UltrasonicSensor sensors[] = {
  { Ultrasonic(27, 14), 0, R },    // Sensor North
  { Ultrasonic(14, 0), 0, -R },    // Sensor South
  { Ultrasonic(25, 26), R, 0 },    // Sensor Right
  { Ultrasonic(32, 33), -R, 0 },   // Sensor Left
};

void setup() {
}

void loop() {
  ultraRead();

// CÁLCULO DAS COORDENADAS DO ROBÔ
  float A = 2 * (sensors[1].x - sensors[0].x);
  float B = 2 * (sensors[1].y - sensors[0].y);
  float C = pow(distances[0], 2) - pow(distances[1], 2) - pow(sensors[0].x, 2) + pow(sensors[1].x, 2) - pow(sensors[0].y, 2) + pow(sensors[1].y, 2);
  float D = 2 * (sensors[3].x - sensors[2].x);
  float E = 2 * (sensors[3].y - sensors[2].y);
  float F = pow(distances[3], 2) - pow(distances[2], 2) - pow(sensors[2].x, 2) + pow(sensors[3].x, 2) - pow(sensors[2].y, 2) + pow(sensors[3].y, 2);

// CÁLCULO DAS COORDENADAS USANDO TRIÂNGULAÇÃO
  x = (C * E - F * B) / (A * E - D * B);
  y = (C * D - F * A) / (B * D - E * A);
}

// FUNÇÃO PARA LEITURA DOS ULTRASSONICOS
void ultraRead() {
  for (int i = 0; i < 4; i++) {
    distances[i] = sensors[i].ultrasonic.read();
    delay(40);
  }
}
