//BIBLIOTECAS
#include <Ultrasonic.h>
#include "MPU9250.h"
#include <Arduino.h>
#include <HardwareSerial.h>

/*
    Usefull links:
    https://en.wikipedia.org/wiki/Magnetic_declination
    https://en.wikipedia.org/wiki/Euler_angles
    https://www.magnetic-declination.com/
*/


//VARIÁVEIS GERAIS ULTRASSONICO
#define R 11
float x, y;
float distances[4];

struct UltrasonicSensor {
  Ultrasonic ultrasonic;
  float x;
  float y;
};

//DEFINIÇÃO DE SENSORES ULTRASSONICOS E SUAS VARIÁVEIS
UltrasonicSensor sensors[] = {
  { Ultrasonic(27, 14), 0, R },    // Sensor North
  { Ultrasonic(14, 0), 0, -R },    // Sensor South
  { Ultrasonic(25, 26), R, 0 },    // Sensor East/Right
  { Ultrasonic(32, 33), -R, 0 },   // Sensor West/Left
};

//VARIAVEIS GERAIS MPU9250
HardwareSerial sender1Serial(2); // UART2
#define SENDER1_TX_PIN 17
#define SENDER1_RX_PIN 16

MPU9250 mpu; 


void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  

    sender1Serial.begin(9600, SERIAL_8N1, SENDER1_RX_PIN, SENDER1_TX_PIN);

    
    /*
    --Magnetic Declination
        IFPE Recife
        Latitude: 8° 3' 31" S
        Longitude: 325° 2' 59" E
        Magnetic Declination: -21° 28'

        Center of Bordeaux
        Latitude: 44° 50' 17.2" N
        Longitude: 359° 25' 35.7" E
        Magnetic Declination: +0° 58'

    */
    mpu.setMagneticDeclination(-21.28); 
    mpu.setFilterIterations(10); //Generally 10-20 is good for stable yaw estimation
    delay(2000);


    /*  need to set all offsets at every bootup by yourself (or calibrate at every bootup).
        Device should be stay still during accel/gyro calibration.
        Round device around during mag calibration.
    */
                 
    //Calibrate (Leave the gyro still for 5s and then make an "8" movement during calibrateMag)
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();
}


void loop() {
    ultraRead();

  // CÁLCULO DAS COORDENADAS DO ROBÔ
    float A = 2 * (sensors[1].x - sensors[0].x);
    float B = 2 * (sensors[1].y - sensors[0].y);
    float C = pow(distances[0], 2) - pow(distances[1], 2) - pow(sensors[0].x, 2) + pow(sensors[1].x, 2) - pow(sensors[0].y, 2) + pow(sensors[1].y, 2);
    float D = 2 * (sensors[3].x - sensors[2].x);
    float E = 2 * (sensors[3].y - sensors[2].y);
    float F = pow(distances[3], 2) - pow(distances[2], 2) - pow(sensors[2].x, 2) + pow(sensors[3].x, 2) - pow(sensors[2].y, 2) + pow(sensors[3].y, 2);

  // CÁLCULO DAS COORDENADAS USANDO TRIÂNGULAÇÃO
    x = (C * E - F * B) / (A * E - D * B);
    y = (C * D - F * A) / (B * D - E * A);
  delay(1000); //precisa?

  // Envia dados pela serial
    sender1Serial.print("[Orientação - Ultra];" + String(x) + ";" + String(y));

    if (mpu.update()) {
        //Serial.print(mpu.getEulerZ()); Serial.print(", ");
        sender1Serial.print("[Orientação - Giro];" + String(mpu.getEulerZ()));
    }

}

// FUNÇÃO PARA LEITURA DOS ULTRASSONICOS
void ultraRead() {
    for (int i = 0; i < 4; i++) {
      distances[i] = sensors[i].ultrasonic.read();
      delay(40);
    }
}
