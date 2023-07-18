//include guards
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <string>

enum MotorDirection {
  FORWARD,
  BACKWARD,
  STOP
};

//PID
extern float desiredYaw;
extern float kp, ki, kd;
extern float previousError;
extern float integral;
extern float ANGLE_THRESHOLD;

void setupPins(int motor[]);
void setupPWM(int motorCanal[], int reso_, int freq_);
void setDirection(int direction_, int motorPin[]);
void processReceivedData(std::string& sender_, std::string& data_);
void moveRobot(float vx_, float vy_);
void inverseKinematics(float theta_, float w_);

//VARIAVEIS GERAIS
#define raio 11

//SENSOR DE COR
#define SDA_PIN_1 5
#define SDA_PIN_2 21
#define SDA_PIN_3 4

#define SCL_PIN 19

//DEFINIR PORTAS MOTORES

//DEFINIR PORTAS PWM
extern float radius;
extern int scalingFactor;
extern int motor1Pin[]; // Não pode
extern int motor2Pin[];
extern int motor3Pin[];
extern int canais[];
extern int motoresPWM[];

//DEFINIR VARIAVEIS PWM
#define freqPWM 20000
#define resolution 9

// Receiver
#define RECEIVER_TX_PIN 17
#define RECEIVER_RX_PIN 16

// Movimentation Variables
extern float v1, v2, v3;
extern float vx, vy, w;
extern int Dir1, Dir2, Dir3;

#define L 8 // distance between robot's center and wheel's center
#define R 4 // wheel's radius

#define sqrt3_2 0.866025404
#define sqrt3 1.73205080757

extern float x, y;
extern float eulerY;
extern float theta, radius;
extern int scalingFactor;

#endif
