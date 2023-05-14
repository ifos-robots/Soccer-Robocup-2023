#include <Arduino.h>
#include "Motor.h"

float v1, v2, v3;
float vx, vy, w;

#define L 8//distance between robot's center and wheel's center
#define sqrt3   1.732050807
#define sqrt3_2 0.866025404

void setup() {
  //CONFIGURANDO PWM
  setupPins(motoresPWM);
  setupPWM(canais, resolution, frequencia);


  //INICIALIZANDO MOTORES
  setupPins(motor1Pin);
  setupPins(motor2Pin);
  setupPins(motor3Pin);

}

void loop() {


}

void inverseKinematics(float vx, float vy, float w) {
    v1 = -((vx - sqrt3 * vy)/2) + L * w;
    v2 = vx + w * L;
    v3 = ((-vx + sqrt3 * vy)/2) + L * w;
}

/*


function inverseKinematics(vx, vy, w)
    v1 = -(vx + math.sqrt(3) * vy) / 2 + L * w
    v2 = vx + w * L
    v3 = (-vx + math.sqrt(3) * vy) / 2 + L * w
    return v1, v2, v3
end
*/