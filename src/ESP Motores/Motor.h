//include guards
#ifndef MOTOR_H
#define MOTO_H

enum MotorDirection {
  FORWARD,
  BACKWARD,
  STOP
};

void setupPins(const int motor[]);
void setupPWM(const int motorCanal[], const int reso, const int freq);
void setDirection(MotorDirection direction, const int motorPin[]);
int porcentagemPWM(float percentualPWM);
float calcDirection();


void moveBackward();
void moveDiagonalRT();
void moveDiagonalLF();
void turnLeft();
void turnRight();
void rotationLeft();
void rotationRight();
void stop();

//VARIAVEIS GERAIS
#define raio 11


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

#endif