//include guards
#ifndef MOTOR_H

#define MOTO_H
#include <HardwareSerial.h>
#include <Arduino.h>

using namespace std;

enum MotorDirection {
  FORWARD,
  BACKWARD,
  STOP
};

void setupPins(const int motor[]);
void setupPWM(const int motorCanal[], const int reso, const int freq);
void setDirection(int direction, const int motorPin[]);
void processReceivedData(const std::string& sender,const std::string& data);
void PWM(float v1, float v2, float v3);
void inverseKinematics(float theta, float w);

int porcentagemPWM(float percentualPWM);


void moveForward();
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
#define freqPWM 20000
#define resolution 8
const int canais[] = {1, 2, 3};

// Receiver
HardwareSerial receiverSerial(2); // UART2
#define RECEIVER_TX_PIN 17
#define RECEIVER_RX_PIN 16


// Movimentation Variables
float v1, v2, v3;
float vx, vy, w;
float minMagnitude = 2;

#define L 8 // distance between robot's center and wheel's center
#define r 4 // wheel's radius
#define sqrt3 1.732050807
#define sqrt3_2 0.866025404

float x; float y;
float eulerY;
float theta; float radius;
const int scalingFactor = 255;

#endif