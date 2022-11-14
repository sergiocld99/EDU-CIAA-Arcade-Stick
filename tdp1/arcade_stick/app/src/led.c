// Cabecera del archivo
#include "led.h"

// Funciones publicas

void LED_Init(){
   gpioInit(PIN_LED_R, GPIO_OUTPUT);
   gpioInit(PIN_LED_G, GPIO_OUTPUT);
   gpioInit(PIN_LED_B, GPIO_OUTPUT);
}

void LED_ApagarTodos(){
   gpioWrite(PIN_LED_R, OFF);
   gpioWrite(PIN_LED_G, OFF);
   gpioWrite(PIN_LED_B, OFF);
}

void LED_EncenderRojo(){
   LED_ApagarTodos();
   gpioWrite(PIN_LED_R, ON);
}

void LED_EncenderVerde(){
   LED_ApagarTodos();
   gpioWrite(PIN_LED_G, ON);
}

void LED_EncenderAzul(){
   LED_ApagarTodos();
   gpioWrite(PIN_LED_B, ON);
}