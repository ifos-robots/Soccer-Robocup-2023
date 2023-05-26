#include <Arduino.h>
#include "Motor.h"
#include <HardwareSerial.h>


//PID
float desiredYaw = 0;
float kp; float ki; float kd;
float previousError;
float integral;
float ANGLE_THRESHOLD = 5;


// Receiver
HardwareSerial receiverSerial(2); // UART2
#define RECEIVER_TX_PIN 17
#define RECEIVER_RX_PIN 16

float v1, v2, v3;
float vx, vy, w;

#define L 8 // distance between robot's center and wheel's center
#define r 4 // wheel's radius
#define sqrt3 1.732050807
#define sqrt3_2 0.866025404

float x; float y;
float eulerY;

void setup(){
    // Serial Communication
    receiverSerial.begin(9600, SERIAL_8N1, RECEIVER_RX_PIN, RECEIVER_TX_PIN);

    // CONFIGURANDO PWM
    setupPins(motoresPWM);
    setupPWM(canais, resolution, frequencia);

    // INICIALIZANDO MOTORES
    setupPins(motor1Pin);
    setupPins(motor2Pin);
    setupPins(motor3Pin);

}
using namespace std;
 
/*The purpose of '&' character is to indicate that the constants 'sender' and 'data' are references, avoiding unnecessary copying of the variables
*/
void processReceivedData(const std::string& sender,const std::string& data){
    int pos = data.find(';');
    if (sender == "[Orientação - Ultra]"){
            std::string x_ = data.substr(0, pos);
            std::string y_ = data.substr(pos + 1, data.find("/"));
            
            //convert values to float
            x = std::stof(x_);
            y = std::stof(y_);

            Serial.print("Received from Sender 1: ");
        }
        else if (sender == "[Orientação - Giro]"){

            std::string eulerY_ = data.substr(pos + 1, data.find("/"));

            //convert angle(string) to float
            eulerY = std::stof(eulerY_);

            Serial.print("Received from Sender 2: ");
        }
        else{
            Serial.println("Received data from unknown sender");
        }
}

void loop(){


    if (receiverSerial.available()){
        /*
        Format: 
        [Orientação - Ultra];10;20/" or 
        [Orientação - Giro];100/"
        
        */

        //Receive data until '/' character is found
        String receivedData = receiverSerial.readStringUntil('/');
        //Convert String from arduino Environment to native C++ string (somehow more reliable)
        std::string stringData = receivedData.c_str();

        // Process received data
        int pos = stringData.find(";");

        if (pos > 0) {
            //
            std::string sender = stringData.substr(0, pos);
            std::string data   = stringData.substr(pos + 1);

            processReceivedData(sender, data);
        }

        
    }

    float alpha = calcDirection();
    vx = cos(alpha);
    vy = sin(alpha);
    float v = sqrt(pow(vx, 2) + pow(vy, 2));
     
    inverseKinematics(vx, vy, 0);
    move(v1, v2, v3);





    //PID Control for angle


    double angleError = eulerY - desiredYaw;

    // Compute PID terms for angle control
    integral += angleError;
    double anglePTerm = kp * angleError;
    double angleITerm = ki * integral;
    double angleDTerm = kd * (angleError - previousError);

    // Compute motor speeds only when angle correction is necessary
    if (abs(angleError) > ANGLE_THRESHOLD) {
        // Compute motor speeds by adjusting the throttle for angle control
        double PIDSpeed =  anglePTerm + angleITerm + angleDTerm;


        if (PIDSpeed > 255){
            PIDSpeed = 255;
        }
        
        ledcWrite(canais[0], PIDSpeed);
        ledcWrite(canais[1], PIDSpeed);
        ledcWrite(canais[2], PIDSpeed);

        previousError = angleError;
    }
    
}

// 255 --- 1600 RPM

void move(float v1, float v2, float v3){

    ledcWrite(canais[0], porcentagemPWM(v1));
    ledcWrite(canais[1], porcentagemPWM(v2));
    ledcWrite(canais[2], porcentagemPWM(v3));

    setDirection(direction(v1), motor1Pin);
    setDirection(direction(v2), motor2Pin);
    setDirection(direction(v3), motor3Pin);

}

MotorDirection direction(float vel){

    if (vel > 0)
    {
        return FORWARD;
    }
    else if (vel < 0)
    {
        return BACKWARD;
    }
    else
    {
        return STOP;
    }
}

void inverseKinematics(float vx, float vy, float w){

    v1 = -((vx - sqrt3 * vy) / 2) + L * w;
    v2 = vx + w * L;
    v3 = ((-vx + sqrt3 * vy) / 2) + L * w;
}