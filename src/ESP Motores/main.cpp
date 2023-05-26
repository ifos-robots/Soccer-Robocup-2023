#include "Motor.h"
#include <HardwareSerial.h>



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

int scalingFactor = 255;

void setup(){
    // Serial Communication
    receiverSerial.begin(9600, SERIAL_8N1, RECEIVER_RX_PIN, RECEIVER_TX_PIN);

    // Configure motors
    setupPins(motoresPWM);
    setupPWM(canais, resolution, freqPWM);

    // Initiate motors
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
    inverseKinematics(theta, w); //Function that calculates the speed of each motor based on the robot's orientation and angular velocity
    delay(50);
}

// 255 --- 1600 RPM

void move_(float v1, float v2, float v3){

    int Dir1 = (v1 > 0) - (v1 < 0);   // returns -1 or 1
    int Dir2 = (v2 > 0) - (v2 < 0);
    int Dir3 = (v3 > 0) - (v3 < 0);

    // reescale values from -5 to 5 to 0 to 255
    int v1 = static_cast<int>(abs((v1 / radius) * scalingFactor));
    int v2 = static_cast<int>(abs((v2 / radius) * scalingFactor));
    int v3 = static_cast<int>(abs((v3 / radius) * scalingFactor));

    ledcWrite(canais[0], v1);
    ledcWrite(canais[1], v2);
    ledcWrite(canais[2], v3);



    setDirection(Dir1, motor1Pin);
    setDirection(Dir2, motor2Pin);
    setDirection(Dir3, motor3Pin);

}



void inverseKinematics(float theta, float w){  
    float vx = radius * cos(theta);
    float vy = radius * sin(theta);

    v1 = -((vx - sqrt3 * vy) / 2) + L * w;
    v2 = vx + w * L;
    v3 = ((-vx + sqrt3 * vy) / 2) + L * w;


    move_(v1, v2, v3); //Function that moves the robot based on the speed of each motor
}
