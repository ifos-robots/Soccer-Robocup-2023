//BIBLIOTECAS

#include <orientation.h>

#define T_MODEA 833

/*
    Usefull links:
    https://en.wikipedia.org/wiki/Magnetic_declination
    https://en.wikipedia.org/wiki/Euler_angles
    https://www.magnetic-declination.com/
*/




void setup() {
    Serial.begin(115200);
    setAllSensorPinsInput();

    Wire.begin();
    
    //MPU9250
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



  // Envia dados pela serial
    sender1Serial.print("[Infravermelhos];"+String(vectorRTWithSma.radius)+";"+String(vectorRTWithSma.theta));

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
