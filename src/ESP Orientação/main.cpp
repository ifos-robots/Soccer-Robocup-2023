//BIBLIOTECAS

#include "orientation.h"
/*
    Usefull links:
    https://en.wikipedia.org/wiki/Magnetic_declination
    https://en.wikipedia.org/wiki/Euler_angles
    https://www.magnetic-declination.com/
*/





void setup() {
    Serial.begin(115200);
    Wire.begin();

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


    /*  need to set all offsets at every bootup by yourself (or calibrate at every bootup).
        Device should be stay still during accel/gyro calibration.
        Round device around during mag calibration.
    */
                 
    //Calibrate (Leave the gyro still for 5s and then make an "8" movement during calibrateMag)
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();
}

using namespace std;

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

  // Envia dados pela serial
    sender1Serial.print("[Orientação - Ultra];" + String(x) + ";" + String(y));

    if (mpu.update()) {
        //Serial.print(mpu.getEulerZ()); Serial.print(", ");
        sender1Serial.print("[Orientação - Giro];" + String(mpu.getEulerZ()));
    }
  delay(50);
}

// FUNÇÃO PARA LEITURA DOS ULTRASSONICOS
void ultraRead() {
    for (int i = 0; i < 4; i++) {
      distances[i] = sensors[i].ultrasonic.read();
      delay(40);
    }
}
