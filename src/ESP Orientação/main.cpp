//BIBLIOTECAS
#include <Ultrasonic.h>

//VARIÁVEIS GERAIS
#define R 11

//VARIAVEIS ULTRASSONICOS - (TRIG, ECHO)
Ultrasonic ultraNorth(27, 14);
Ultrasonic ultraSouth(14, 0);
Ultrasonic ultraRight(25, 26);
Ultrasonic ultraLeft(32, 33);
float distanceNorth, distanceSouth, distanceRight, distanceLeft;
float x, y;

void setup() {

}

void loop() {
//LEITURA DOS ULTRASSONICOS
  distanceNorth = ultraNorth.read();
  distanceSouth = ultraSouth.read();
  distanceRight = ultraRight.read();
  distanceLeft = ultraLeft.read();
}

//FUNÇÃO PARA ADQUIRIR COORDENADAS
float* getCoordinates(float distanceN, float distanceS, float distanceR, float distanceL){
  float coordenada[2];
  if(distanceN > distanceS){
    y = (distanceN - distanceS) + R;
  } else {
    y = (distanceS - distanceN) + R;
  }
  if(distanceR > distanceL){
    x = (distanceR - distanceL) + R;
  } else {
    x = (distanceL - distanceR) + R;
  }
  coordenada[0] = x;
  coordenada[1] = y;
  return coordenada;
}
