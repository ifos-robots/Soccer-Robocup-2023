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
    break;
    
    case -1:
        digitalWrite(motorPin[0], LOW);
        digitalWrite(motorPin[1], HIGH);
    break;

    case 0:
        digitalWrite(motorPin[0], LOW);
        digitalWrite(motorPin[1], LOW);
    break;

  }
}

// 255 --- 1600 RPM

void moveRobot(float vx, float vy){

    v1 = -((vx - sqrt3 * vy) / 2) + L * w;
    v2 = vx + w * L;
    v3 = ((-vx + sqrt3 * vy) / 2) + L * w;

    // set direction
    Dir1 = (v1 > 0) - (v1 < 0);   // returns -1 or 1
    Dir2 = (v2 > 0) - (v2 < 0);
    Dir3 = (v3 > 0) - (v3 < 0);

    // reescale values from -5 to 5 to 0 to 255
    v1 = static_cast<int>(abs((v1 / radius) * scalingFactor));
    v2 = static_cast<int>(abs((v2 / radius) * scalingFactor));
    v3 = static_cast<int>(abs((v3 / radius) * scalingFactor));

    ledcWrite(canais[0], v1);
    ledcWrite(canais[1], v2);
    ledcWrite(canais[2], v3);



    setDirection(Dir1, motor1Pin);
    setDirection(Dir2, motor2Pin);
    setDirection(Dir3, motor3Pin);

}

void inverseKinematics(float theta, float w){  
    vx = radius * cos(theta);
    vy = radius * sin(theta);

    moveRobot(vx, vy);

}



void processReceivedData(const std::string& sender,const std::string& data){
  /*The purpose of '&' character is to indicate that the constants 'sender' and 'data' are references, avoiding unnecessary copying of the variables
  */
 
    int pos = data.find(';');
    if (sender == "[Orientação - Ultra]"){
            std::string x_ = data.substr(0, pos);
            std::string y_ = data.substr(pos + 1, data.find("/") - (pos + 1));
            
            //convert values to float
            x = std::stof(x_);
            y = std::stof(y_);

        }
        else if (sender == "[Orientação - Giro]"){


            std::string eulerY_ = data.substr(pos + 1, data.find("/") - (pos + 1));

            //convert angle to float
            eulerY = std::stof(eulerY_);


        }
        else if (sender == "[Infravermelhos]"){
        std::string radius_ = data.substr(pos + 1, data.find("/") - (pos + 1));
        std::string theta_ = data.substr(data.find("/") + 1);

            //convert angle to float
            theta = std::stof(theta_);
            radius = std::stof(radius_);


        }
        else{
            
        }
}


int scalePWM(float percentualmovePWM) {
  int valormovePWM = (percentualmovePWM * 255) / 100;
  return valormovePWM;
}




void moveForward() {
  ledcWrite(canais[0], scalePWM(73*0.866));
  ledcWrite(canais[1], scalePWM(0));
  ledcWrite(canais[2], scalePWM(73*0.866));

  setDirection(-1, motor1Pin);
  setDirection(0, motor2Pin);
  setDirection(1, motor3Pin);

}

void moveBackward() {
  ledcWrite(canais[0], scalePWM(73*0.866));
  ledcWrite(canais[1], scalePWM(0));
  ledcWrite(canais[2], scalePWM(73*0.866));

  setDirection(1, motor1Pin);
  setDirection(0, motor2Pin);
  setDirection(-1, motor3Pin);
}

void moveDiagonalRT() {
  ledcWrite(canais[0], scalePWM(73));
  ledcWrite(canais[1], scalePWM(73));
  ledcWrite(canais[2], scalePWM(73));
  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}
//Move na diagonal para esquerda ou direita
void moveDiagonalLF() {
  ledcWrite(canais[0], scalePWM(73*0.366));
  ledcWrite(canais[1], scalePWM(73));
  ledcWrite(canais[2], scalePWM(73));
  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}

void turnLeft() {
  ledcWrite(canais[0], scalePWM(73*0.5));
  ledcWrite(canais[1], scalePWM(73));
  ledcWrite(canais[2], scalePWM(73*0.5));
  setDirection(1, motor1Pin);
  setDirection(-1, motor2Pin);
  setDirection(1, motor3Pin);
}

void turnRight() {
  ledcWrite(canais[0], scalePWM(73*0.5));
  ledcWrite(canais[1], scalePWM(73));
  ledcWrite(canais[2], scalePWM(73*0.5));
  setDirection(-1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(-1, motor3Pin);
}

void rotationLeft() {
  ledcWrite(canais[0], scalePWM(73));
  ledcWrite(canais[1], scalePWM(73));
  ledcWrite(canais[2], scalePWM(73));
  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}

void rotationRight() {
  ledcWrite(canais[0], scalePWM(73));
  ledcWrite(canais[1], scalePWM(73));
  ledcWrite(canais[2], scalePWM(73));
  setDirection(-1, motor1Pin);
  setDirection(-1, motor2Pin);
  setDirection(-1, motor3Pin);
}

void stop() {
  ledcWrite(canais[0], scalePWM(0));
  ledcWrite(canais[1], scalePWM(0));
  ledcWrite(canais[2], scalePWM(0));

  setDirection(1, motor1Pin);
  setDirection(1, motor2Pin);
  setDirection(1, motor3Pin);
}



/*OBS:

73 é devido ao moveDiagonal pq 1.366 * 100 resultaria num valor maior que o ciclo máximo do movePWM. Utilizando 73 como valor mínimo, resulta: 73*1.366 ~= 98.
Não é a melhor solução mas como essa parte é só para testes vai funcionar.

*/