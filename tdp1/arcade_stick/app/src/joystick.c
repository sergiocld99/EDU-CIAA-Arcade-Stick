// Este módulo es el único que tiene acceso directo a las funciones del ADC
#include "joystick.h"

// Variables privadas
static bool_t up, left, right, down;


void Joystick_Init(){
   // Inicializar y habilitar ADC
   adcConfig(ADC_ENABLE);

   // Asignar pin conectado al Switch como entrada digital
   gpioInit(PIN_SW, GPIO_INPUT);
}

uint16_t Joystick_LeerX(){
   uint16_t raw = adcRead(PIN_VRX);

   left = (raw < NEUTRO_MIN);
   right = (raw > NEUTRO_MAX);

   return raw;
}


uint16_t Joystick_LeerY(){
   uint16_t raw = adcRead(PIN_VRY);

   up = (raw < NEUTRO_MIN);
   down = (raw > NEUTRO_MAX);

   return raw;
}

bool_t Joystick_LeerSwitch(){
   return !gpioRead(PIN_SW);
}

void Joystick_GetDirs(bool_t* dirUp, bool_t* dirLeft, bool_t* dirRight, bool_t* dirDown){
   *dirUp = up;
   *dirLeft = left;
   *dirRight = right;
   *dirDown = down;
}
