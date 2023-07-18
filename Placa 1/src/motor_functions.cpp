#include "Motor.h"
#include "Arduino.h"


float radius = 5;
int scalingFactor = 511;
int motor1Pin[] = {8, 5}; // Remove the initialization here
int motor2Pin[] = {11, 12};
int motor3Pin[] = {14, 15};
int canais[] = {1, 2, 3};
int motoresPWM[] = {10, 13, 16};

float desiredYaw;
float kp, ki, kd;
float previousError;
float integral;
float ANGLE_THRESHOLD;

float v1, v2, v3;
float vx, vy, w;
int Dir1, Dir2, Dir3;

float x, y;
float eulerY;
float theta;


void setupPins(int motor[]){
        for (int i = 0; i < 2; i++){
          pinMode(motor[i], OUTPUT);
        }
}
void setupPWM(int motorCanal[], int reso, int freq){
        for (int i = 0; i < 3; i++){
          ledcSetup(motorCanal[i], freq, reso);
          ledcAttachPin(motorCanal[i], i+1);
        }
}


//Define motor direction
void setDirection(int direction, int motorPin[]){
    
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
    v1 = static_cast<int>(abs((v1 / radius) * scalingFactor)); //diminuir radius do (v1/radius) para aumentar ciclo pwm manualmente
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



void processReceivedData(std::string& sender,std::string& data){
  /*The purpose of '&' character is to indicate that the nts 'sender' and 'data' are references, avoiding unnecessary copying of the variables
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
        else if (sender == "[TEST]"){
            std::string theta = data.substr(pos + 1, data.find("/") - (pos + 1));
            std::string w = data.substr(data.find("/") + 1);

            //convert angle to float
            theta = std::stof(theta);
            w = std::stof(w);
        }

}
