/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _JOYSTICK_H_
   #define _JOYSTICK_H_

   /*==================[inclusiones]============================================*/
   //#include "sapi.h"
   #include "sapi_adc.h"      // adcInit() y adcRead()
   #include "sapi_gpio.h"     // gpioInit()

   #include "mapeoGpio.h"     // define pines SW, VRx, VRy

   #include <stdlib.h>

   /*==================[macros]=================================================*/
   
   #define NEUTRO_MIN 400
   #define NEUTRO_MAX 624

   /*==================[declaraciones de funciones públicas]====================*/
   
   // Habilita el ADC y establece pin conectado al Switch
   void Joystick_Init();

   // Lee el valor del eje X y produce resultado digital entre 0 y 1023
   uint16_t Joystick_LeerX();

   // Lee el valor del eje Y y produce resultado digitañ entre 0 y 1023
   uint16_t Joystick_LeerY();

   void Joystick_GetDirs(bool_t* dirUp, bool_t* dirLeft, bool_t* dirRight, bool_t* dirDown);
   
   /*==================[end of file]============================================*/

#endif /* _JOYSTICK_H_ */