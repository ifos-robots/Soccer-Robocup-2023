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

//Define motor direction
void setDirection(int direction, const int motorPin[]){
  
  switch (direction){
    case 1:
        digitalWrite(motorPin[0], HIGH);
        digitalWrite(motorPin[1], LOW);
    
    case -1:
        digitalWrite(motorPin[0], LOW);
        digitalWrite(motorPin[1], HIGH);
    
    case 0:
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

  setDirection(-1, motor1Pin);
  setDirection(0, motor2Pin);
  setDirection(1, motor3Pin);

}

void moveBackward() {
  ledcWrite(canais[0], porcentagemPWM(73*0.866));
  ledcWrite(canais[1], porcentagemPWM(0));
  ledcWrite(canais[2], porcentagemPWM(73*0.866));

  setDirection(1, motor1Pin);
  setDirection(0, motor2Pin);
  setDirection(-1, motor3Pin);
}

void moveDiagonalRT() {
  ledcWrite(canais[0], porcentagemPWM(73));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}
//Move na diagonal para esquerda ou direita
void moveDiagonalLF() {
  ledcWrite(canais[0], porcentagemPWM(73*0.366));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}

void turnLeft() {
  ledcWrite(canais[0], porcentagemPWM(73*0.5));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73*0.5));
  setDirection(1, motor1Pin);
  setDirection(-1, motor2Pin);
  setDirection(1, motor3Pin);
}

void turnRight() {
  ledcWrite(canais[0], porcentagemPWM(73*0.5));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73*0.5));
  setDirection(-1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(-1, motor3Pin);
}

void rotationLeft() {
  ledcWrite(canais[0], porcentagemPWM(73));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}

void rotationRight() {
  ledcWrite(canais[0], porcentagemPWM(73));
  ledcWrite(canais[1], porcentagemPWM(73));
  ledcWrite(canais[2], porcentagemPWM(73));
  setDirection(-1, motor1Pin);
  setDirection(-1, motor2Pin);
  setDirection(-1, motor3Pin);
}

void STOP() {
  ledcWrite(canais[0], porcentagemPWM(0));
  ledcWrite(canais[1], porcentagemPWM(0));
  ledcWrite(canais[2], porcentagemPWM(0));

  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}



/*OBS:

73 é devido ao moveDiagonal pq 1.366 * 100 resultaria num valor maior que o ciclo máximo do pwm. Utilizando 73 como valor mínimo, resulta: 73*1.366 ~= 98.
Não é a melhor solução mas como essa parte é só para testes vai funcionar.

*/