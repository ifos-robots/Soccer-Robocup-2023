#include <Arduino.h>

float error_prior = 0;
float integral_prior = 0;
//KP = Some value you need to come up (see tuning section below)
//KI = Some value you need to come up (see tuning section below)
//KD = Some value you need to come up (see tuning section below)
float KP = 0.5;
float KI = 0.2;
float KD = 0.4;

float bias = 0;
float const desired_value = 0;
float integral; float derivative; float iteration_time; float output;



int main(){

    while(1) {
        float error = desired_value - actual_value;
        integral = integral_prior + error * iteration_time;
        derivative = (error - error_prior) / iteration_time;
        output = KP*error + KI*integral + KD*derivative + bias;
        error_prior = error;
        integral_prior = integral;
        sleep(iteration_time);
    }





    return 0;
}