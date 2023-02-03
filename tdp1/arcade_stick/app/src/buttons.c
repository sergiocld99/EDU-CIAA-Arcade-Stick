#include "buttons.h"

void Buttons_Init(){
    // Establecer cada pin conectado a un botón como entrada
    gpioInit(PIN_S1, GPIO_INPUT);
    gpioInit(PIN_S2, GPIO_INPUT);
    gpioInit(PIN_S3, GPIO_INPUT);
    gpioInit(PIN_S4, GPIO_INPUT);
    gpioInit(PIN_S5, GPIO_INPUT);
    gpioInit(PIN_S6, GPIO_INPUT);
}