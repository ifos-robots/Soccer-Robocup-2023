#include "Motor.h"



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

 
/*The purpose of '&' character is to indicate that the constants 'sender' and 'data' are references, avoiding unnecessary copying of the variables
*/


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






