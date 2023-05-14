#include <Arduino.h>


//VARIAVEIS GERAIS
#define R 11


//DEFINIR PORTAS MOTORES
const int motor1Pin[] = {32, 33};
const int motor2Pin[] = {27, 26};
const int motor3Pin[] = {4, 0};


//DEFINIR PORTAS PWM
int const motoresPWM[] = {25, 14, 2};


//DEFINIR VARIAVEIS PWM
#define frequencia 20000
#define resolution 8
const int canais[] = {1, 2, 3};


void setupPins(const int motor[]){
        for (int i = 0; i < 2; i++){
          pinMode(motor[i], OUTPUT);
        }
}
void setupPWM(const int motorCanal[]){
        for (int i = 0; i < 3; i++){
          ledcSetup(motorCanal[i], frequencia, resolution);
          ledcAttachPin(motorCanal[i], i+1);
        }
}
void setup() {
  //CONFIGURANDO PWM
  setupPins(motoresPWM);
  setupPWM(canais);


  //INICIALIZANDO MOTORES
  setupPins(motor1Pin);
  setupPins(motor2Pin);
  setupPins(motor3Pin);

}

void loop() {


}


//REGRA DE 3 PARA PWM (0-100/0-255)
int porcentagemPWM(float percentualPWM) {
  int valorPWM = (percentualPWM * 255) / 100;
  return valorPWM;
}

//FUNCOES PARA DEFINIR A DIRECAO DA ROTACAO DO MOTOR
void setDirection(bool direction,const int motorPin[]){
    if (direction == 1) {
        digitalWrite(motorPin[0], HIGH);
        digitalWrite(motorPin[1], LOW);
    }
    else if (direction == -1) {
        digitalWrite(motorPin[0], LOW);
        digitalWrite(motorPin[1], HIGH);
    }
    else {
        digitalWrite(motorPin[0], LOW);
        digitalWrite(motorPin[1], LOW);
    }
}



//FUNCOES DE MOVIMENTACAO

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

void stop() {
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