#include <Arduino.h>
#include <Motor.h>

//VARIAVEIS GERAIS
#define raio 11


//DEFINIR PORTAS MOTORES
const int motor1Pin[] = {32, 33};
const int motor2Pin[] = {27, 26};
const int motor3Pin[] = {4, 0};

//DEFINIR PORTAS PWM
int const motoresPWM[] = {25, 14, 2};


//DEFINIR VARIAVEIS PWM
#define frequencia 20000
#define resolution 8
const int canais[] = {1, 2, 3};



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


//REGRA DE 3 PARA PWM (0-100/0-255)





//FUNCOES DE MOVIMENTACAO


/*OBS:

73 é devido ao moveDiagonal pq 1.366 * 100 resultaria num valor maior que o ciclo máximo do pwm. Utilizando 73 como valor mínimo, resulta: 73*1.366 ~= 98.
Não é a melhor solução mas como essa parte é só para testes vai funcionar.

*/