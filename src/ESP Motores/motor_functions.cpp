#include "Motor.h"
#include "Arduino.h"

void setupPins(const int motor[]){
        for (int i = 0; i < 2; i++){
          pinMode(motor[i], OUTPUT);
        }
}
void setupPWM(const int motorCanal[], const int reso, const int freq){
        for (int i = 0; i < 3; i++){
          ledcSetup(motorCanal[i], freq, reso);
          ledcAttachPin(motorCanal[i], i+1);
        }
}

//FUNCOES PARA DEFINIR A DIRECAO DA ROTACAO DO MOTOR
void setDirection(MotorDirection direction,const int motorPin[]){
    if (direction == FORWARD) {
        digitalWrite(motorPin[0], HIGH);
        digitalWrite(motorPin[1], LOW);
    }
    else if (direction == BACKWARD) {
        digitalWrite(motorPin[0], LOW);
        digitalWrite(motorPin[1], HIGH);
    }
    else if (direction == STOP)  {
        digitalWrite(motorPin[0], LOW);
        digitalWrite(motorPin[1], LOW);
    }
}

int porcentagemPWM(float percentualPWM) {
  int valorPWM = (percentualPWM * 255) / 100;
  return valorPWM;
}




void moveForward() {
  ledcWrite(canais[0], porcentagemPWM(73*0.866));
  ledcWrite(canais[1], porcentagemPWM(0));
  ledcWrite(canais[2], porcentagemPWM(73*0.866));

  setDirection(BACKWARD, motor1Pin);
  setDirection(STOP, motor2Pin);
  setDirection(FORWARD, motor3Pin);

}

void moveBackward() {
  ledcWrite(canais[0], porcentagemPWM(73*0.866));
  ledcWrite(canais[1], porcentagemPWM(0));
  ledcWrite(canais[2], porcentagemPWM(73*0.866));
  setDirection(FORWARD, motor1Pin);
  setDirection(STOP, motor2Pin);
  setDirection(BACKWARD, motor3Pin);
}

void moveDiagonalRT() {
  ledcWrite(canais[0], porcentagemPWM(73));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(FORWARD, motor1Pin);
  setDirection(FORWARD, motor2Pin);
  setDirection(FORWARD, motor3Pin);
}
//Move na diagonal para esquerda ou direita
void moveDiagonalLF() {
  ledcWrite(canais[0], porcentagemPWM(73*0.366));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(FORWARD, motor1Pin);
  setDirection(FORWARD, motor2Pin);
  setDirection(FORWARD, motor3Pin);
}

void turnLeft() {
  ledcWrite(canais[0], porcentagemPWM(73*0.5));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73*0.5));
  setDirection(FORWARD, motor1Pin);
  setDirection(BACKWARD, motor2Pin);
  setDirection(FORWARD, motor3Pin);
}

void turnRight() {
  ledcWrite(canais[0], porcentagemPWM(73*0.5));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73*0.5));
  setDirection(BACKWARD, motor1Pin);
  setDirection(FORWARD, motor2Pin);
  setDirection(BACKWARD, motor3Pin);
}

void rotationLeft() {
  ledcWrite(canais[0], porcentagemPWM(73));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(FORWARD, motor1Pin);
  setDirection(FORWARD, motor2Pin);
  setDirection(FORWARD, motor3Pin);
}

void rotationRight() {
  ledcWrite(canais[0], porcentagemPWM(73));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(BACKWARD, motor1Pin);
  setDirection(BACKWARD, motor2Pin);
  setDirection(BACKWARD, motor3Pin);
}

void stop() {
  ledcWrite(canais[0], porcentagemPWM(0));
  ledcWrite(canais[1], porcentagemPWM(0));
  ledcWrite(canais[2], porcentagemPWM(0));

  setDirection(FORWARD, motor1Pin);
  setDirection(FORWARD, motor2Pin);
  setDirection(FORWARD, motor3Pin);
}