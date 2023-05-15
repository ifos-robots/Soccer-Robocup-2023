#include <Arduino.h>
#include "Motor.h"

float v1, v2, v3;
float vx, vy, w;

#define L 8 //distance between robot's center and wheel's center
#define r 4 // wheel's radius 
#define sqrt3   1.732050807
#define sqrt3_2 0.866025404

void setup() {
  //CONFIGURANDO PWM
  setupPins(motoresPWM);
  setupPWM(canais, resolution, frequencia);


  //INICIALIZANDO MOTORES
  setupPins(motor1Pin);
  setupPins(motor2Pin);
  setupPins(motor3Pin);

}

void loop() {

    float alpha = calcDirection(); 
    vx = cos(alpha);
    vy = sin(alpha);
    inverseKinematics(vx, vy, 0);
    move(v1, v2, v3);

}

    //255 --- 1600 RPM

void move(float v1, float v2, float v3) {

    ledcWrite(canais[0], porcentagemPWM(v1));
    ledcWrite(canais[1], porcentagemPWM(v2));
    ledcWrite(canais[2], porcentagemPWM(v3));

    setDirection(direction(v1), motor1Pin);
    setDirection(direction(v2), motor2Pin);
    setDirection(direction(v3), motor3Pin);

}

MotorDirection direction(float vel){
    if (vel > 0) {
        return FORWARD;
    }
    else if (vel < 0) {
        return BACKWARD;
    }
    else {
        return STOP;
    }
}


void inverseKinematics(float vx, float vy, float w) {
    v1 = -((vx - sqrt3 * vy)/2) + L * w;
    v2 = vx + w * L;
    v3 = ((-vx + sqrt3 * vy)/2) + L * w;
}