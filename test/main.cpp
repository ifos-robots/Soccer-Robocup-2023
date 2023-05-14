//BIBLIOTECAS
#include <Ultrasonic.h>

//VARIAVEIS GERAIS
#define RoboRaio 11

//DEFINIR PORTAS MOTORES
#define motorXDir1 32
#define motorXDir2 33
#define motorYDir1 27
#define motorYDir2 26
#define motorZDir1 4
#define motorZDir2 0

//DEFINIR PORTAS PWM
#define motorXPWM 25
#define motorYPWM 14
#define motorZPWM 2

//DEFINIR VARIAVEIS PWM
#define frequencia 20000
#define motorXCanal 1
#define motorYCanal 2
#define motorZCanal 3
#define resolution 8

//DEFINIR VARIAVEIS ULTRASSONICO - (trig, echo)
Ultrasonic ultraX1(27, 14);
Ultrasonic ultraX2(4, 0);
Ultrasonic ultraY1(25, 26);
Ultrasonic ultraY2(32, 33);
float distanceX1, distanceX2, distanceY1, distanceY2;

//DEFINIR TAMANHO CAMPO
const float campo[] = {93, 100};
float x, y;

void setup() {
  //CONFIGURANDO PWM
  pinMode(motorXPWM, OUTPUT);
  pinMode(motorYPWM, OUTPUT);
  pinMode(motorZPWM, OUTPUT);
  ledcSetup(motorXCanal, frequencia, resolution);
  ledcSetup(motorYCanal, frequencia, resolution);
  ledcSetup(motorZCanal, frequencia, resolution);
  ledcAttachPin(motorXPWM, 1);
  ledcAttachPin(motorYPWM, 2);
  ledcAttachPin(motorZPWM, 3);

  //INICIALIZANDO MOTORES
  pinMode(motorXDir1, OUTPUT);
  pinMode(motorXDir2, OUTPUT);
  pinMode(motorYDir1, OUTPUT);
  pinMode(motorYDir2, OUTPUT);
  pinMode(motorZDir1, OUTPUT);
  pinMode(motorZDir2, OUTPUT);
}

void loop() {
//LEITURA ULTRASSONICO
  distanceX1 = ultraX1.read();
  distanceX2 = ultraX2.read();
  distanceY1 = ultraY1.read();
  distanceY2 = ultraY2.read();

//MOVIMENTAÇAO ULTRASSONICO
  float* coordenadas = getCordinates(distanceX1, distanceX2, distanceY1, distanceY2);
  x = coordenadas[0];
  y = coordenadas[1];
  
  if(x > campo[0] && y > campo[1]){
    moveDiagonalRT();
  }
  else if(x = campo[0]){
    moveForward();
  }
}

//FUNCAO PARA CALCULAR AS COORDENADAS DO CAMPO
float* getCordinates(float distance_X1, float distance_X2, float distance_Y1, float distance_Y2) {
  float* coordinates = new float[2];
  if(distance_X1 > distance_X2){
    x = (distance_X1 + RoboRaio) - distance_X2;
  } else {
    x = (distance_X2 + RoboRaio) - distance_X1;
  }
  if(distance_Y1 > distance_Y2){
    y = (distance_Y1 + RoboRaio) - distance_Y2;
  } else {
    y = (distance_Y2 + RoboRaio) - distance_Y1;
  }
  coordinates[0] = x;
  coordinates[1] = y;
  return coordinates;
}

//REGRA DE 3 PARA PWM (0-100/0-255)
int porcentagemPWM(float percentualPWM) {
  int valorPWM = (percentualPWM * 255) / 100;
  return valorPWM;
}

//FUNCOES PARA DEFINIR A DIRECAO DA ROTACAO DO MOTOR
int setDirectionMotorX(int direction) {
  if (direction == 1) {
    digitalWrite(motorXDir1, HIGH);
    digitalWrite(motorXDir2, LOW);
  } else if (direction == -1) {
    digitalWrite(motorXDir1, LOW);
    digitalWrite(motorXDir2, HIGH);
  }
  return direction;
}

int setDirectionMotorY(int direction) {
  if (direction == 1) {
    digitalWrite(motorYDir1, HIGH);
    digitalWrite(motorYDir2, LOW);
  } else if (direction == -1) {
    digitalWrite(motorYDir1, LOW);
    digitalWrite(motorYDir2, HIGH);
  }
  return direction;
}

int setDirectionMotorZ(int direction) {
  if (direction == 1) {
    digitalWrite(motorZDir1, HIGH);
    digitalWrite(motorZDir2, LOW);
  } else if (direction == -1) {
    digitalWrite(motorZDir1, LOW);
    digitalWrite(motorZDir2, HIGH);
  }
  return direction;
}

//FUNCOES DE MOVIMENTACAO
void moveForward() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void moveBackward() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void moveDiagonalRT() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void moveDiagonalLF() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void moveLeft() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void moveRight() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void rotationLeft() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void rotationRight() {
  ledcWrite(motorXCanal, porcentagemPWM(100));
  ledcWrite(motorYCanal, porcentagemPWM(100));
  ledcWrite(motorZCanal, porcentagemPWM(100));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}

void stop() {
  ledcWrite(motorXCanal, porcentagemPWM(0));
  ledcWrite(motorYCanal, porcentagemPWM(0));
  ledcWrite(motorZCanal, porcentagemPWM(0));
  setDirectionMotorX(1);
  setDirectionMotorY(1);
  setDirectionMotorZ(1);
}
