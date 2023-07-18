
#include <NewPing.h>
#include <orientation.h>


NewPing sonarLeste(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_X);
NewPing sonarOeste(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE_X);
NewPing sonarNorte(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE_Y);
NewPing sonarSul(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE_Y);