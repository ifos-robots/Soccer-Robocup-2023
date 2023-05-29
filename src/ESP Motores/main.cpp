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






