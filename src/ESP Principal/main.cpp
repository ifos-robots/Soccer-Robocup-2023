#include "Motor.h"
#include "Adafruit_TCS34725.h"


#define I2C_TCS1_SDA 
#define I2C_TCS1_SCL 32

#define I2C_TCS2_SDA 33
#define I2C_TCS2_SCL 32

uint16_t r1, g1, b1, c1;
uint16_t r2, g2, b2, c2;
uint16_t r3, g3, b3, c3;

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_540MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_540MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_540MS, TCS34725_GAIN_1X);


// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}



void setup(){
    // Start I2C communication with the Multiplexer
    Wire.begin();


    TCA9548A (0); // Select I2C BUS 0
    tcs1.begin(0x29); //TCS34725 0x29
    
    TCA9548A (1); // Select I2C BUS 1
    tcs2.begin(0x29); //TCS34725 0x29

    TCA9548A (2); // Select I2C BUS 2
    tcs3.begin(0x29); //TCS34725 0x29


    



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

    TCA9548A (0);
    tcs1.getRawData(&r1, &g1, &b1, &c1);
    TCA9548A (1);
    tcs2.getRawData(&r2, &g2, &b2, &c2);
    TCA9548A (2);
    tcs3.getRawData(&r3, &g3, &b3, &c3);


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






bool checkLine(uint16_t r, uint16_t g, uint16_t b){

    if (abs(r - g) < 20 && abs(r - b) < 20 && abs(g - b) < 20) {
        Serial.println("Detected white color!");
        // Perform desired action for white color
        return true;
    }
    else {
        // Perform desired action for non-white color
        return false;
    }

}