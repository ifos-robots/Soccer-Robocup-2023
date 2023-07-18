//#include <Motor.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Motor.h>

//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_540MS, TCS34725_GAIN_1X);

HardwareSerial receiverSerial(0);

void setup(){




    // Start I2C communication with the Multiplexer
    Wire.begin();

    // Serial Communication
    receiverSerial.begin(115200, SERIAL_8N1, RECEIVER_RX_PIN, RECEIVER_TX_PIN);

    // Configure motors
    setupPins(motoresPWM);
    setupPWM(canais, resolution, freqPWM);

    // Initiate motors
    setupPins(motor1Pin);
    setupPins(motor2Pin);
    setupPins(motor3Pin);


}


void loop(){

    //Get RGB values from each sensor
    // selTCS34725(1);
    // selTCS34725(2);
    // selTCS34725(3);



    // correctRobotDirection(checkLineState());
    


//inverter direção motor 1

    // Get theta and w
    if (receiverSerial.available()){
        /*
        Format: 
        [Orientação - Ultra];10;20/" or 
        [Orientação - Giro];100/"
        or
        [TEST];angulo;vec. angular;/
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
        //[Teste];1.5708;/ (Angle in rad)

        
    }
   
   
    inverseKinematics(theta, w); //Function that calculates the speed of each motor based on the robot's orientation and angular velocity
    delay(50);


    // //PID Control for angle correction
    // double angleError = eulerY - desiredYaw;

    // // Compute PID terms for angle control
    // integral += angleError;
    // double anglePTerm = kp * angleError;
    // double angleITerm = ki * integral;
    // double angleDTerm = kd * (angleError - previousError);

    // // Compute motor speeds only when angle correction is necessary
    // if (abs(angleError) > ANGLE_THRESHOLD) {
    //     // Compute motor speeds by adjusting the throttle for angle control
    //     double PIDSpeed =  anglePTerm + angleITerm + angleDTerm;


    //     if (PIDSpeed > 255){
    //         PIDSpeed = 255;
    //     }
        
    //     ledcWrite(canais[0], PIDSpeed);
    //     ledcWrite(canais[1], PIDSpeed);
    //     ledcWrite(canais[2], PIDSpeed);

    //     previousError = angleError;
    // }
}





// void selTCS34725(int sensorNum){
//     if (sensorNum == 1) {
//         Wire.begin(SDA_PIN_1, SCL_PIN);

//         tcs.getRawData(&r1, &g1, &b1, &c1);  
        
//         Wire.end();
//     }
//     else if (sensorNum == 2) {
//         Wire.begin(SDA_PIN_2, SCL_PIN);

//         tcs.getRawData(&r2, &g2, &b2, &c2);  
        
//         Wire.end();
//     }
//     else if (sensorNum == 3){
//         Wire.begin(SDA_PIN_3, SCL_PIN);

//         tcs.getRawData(&r3, &g3, &b3, &c3);  
        
//         Wire.end();
//     }

// }

