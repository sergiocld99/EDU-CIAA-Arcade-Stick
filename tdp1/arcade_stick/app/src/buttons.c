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

void Buttons_Read(bool_t* values){
    values[0] = !gpioRead(PIN_S1);
    values[1] = !gpioRead(PIN_S2);
    values[2] = !gpioRead(PIN_S3);
    values[3] = !gpioRead(PIN_S4);
    values[4] = !gpioRead(PIN_S5);
    values[5] = !gpioRead(PIN_S6);
}