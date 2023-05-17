#include "MPU9250.h"
#include <Arduino.h>


/*
    Usefull links:
    https://en.wikipedia.org/wiki/Magnetic_declination
    https://en.wikipedia.org/wiki/Euler_angles
    https://www.magnetic-declination.com/
*/



MPU9250 mpu; 

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  
    /*
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
    delay(5000);


    /*  need to set all offsets at every bootup by yourself (or calibrate at every bootup).
        Device should be stay still during accel/gyro calibration.
        Round device around during mag calibration.
    */


    //mpu.selectFilter
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();
}

void loop() {
    if (mpu.update()) {
        Serial.print(mpu.getEulerZ()); Serial.print(", ");
    }
}
