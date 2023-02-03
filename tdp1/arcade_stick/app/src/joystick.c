#include "joystick.h"

// Este módulo es el único que tiene acceso directo a las funciones del ADC

void Joystick_Init(){
   // Inicializar y habilitar ADC
   adcConfig(ADC_ENABLE);

   // Asignar pin conectado al Switch como entrada digital
   gpioInit(PIN_SW, GPIO_INPUT);
}


uint16_t Joystick_LeerX(){
   return adcRead(PIN_VRX);
}


uint16_t Joystick_LeerY(){
   return adcRead(PIN_VRY);
}

Joystick_Direccion Joystick_ProcesarDir(uint16_t valorEjeX, uint16_t valorEjeY){
   /*
   if (valorEjeX > NEUTRO_MIN && valorEjeX < NEUTRO_MAX){
      if (valorEjeY > NEUTRO_MIN && valorEjeY < NEUTRO_MAX) return NONE;
      else if (valorEjeY <= NEUTRO_MIN) return UP;
      else return DOWN;
   } else if (valorEjeX <= NEUTRO_MIN) return LEFT;
   else return RIGHT;
   */
}


void Joystick_LeerDirs(uint16_t valorEjeX, uint16_t valorEjeY, Joystick_Direccion* dirs){
   if (valorEjeX > NEUTRO_MIN && valorEjeX < NEUTRO_MAX) dirs[0] = NONE;
   else if (valorEjeX <= NEUTRO_MIN) dirs[0] = LEFT;
   else dirs[0] = RIGHT;
      
   if (valorEjeY > NEUTRO_MIN && valorEjeY < NEUTRO_MAX) dirs[1] = NONE;
   else if (valorEjeY <= NEUTRO_MIN) dirs[1] = UP;
   else dirs[1] = DOWN;
}