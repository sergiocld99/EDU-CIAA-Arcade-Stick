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

   /*==================[tipos de datos declarados por el usuario]===============*/
   typedef enum {
      UP, LEFT, RIGHT, DOWN, NONE
   } Joystick_Direccion;

   /*==================[declaraciones de datos externos]========================*/

   /*==================[declaraciones de funciones p�blicas]====================*/
   
   // Habilita el ADC y establece pin conectado al Switch
   void Joystick_Init();

   // Lee el valor del eje X y produce resultado digital entre 0 y 1023
   uint16_t Joystick_LeerX();

   // Lee el valor del eje Y y produce resultado digitañ entre 0 y 1023
   uint16_t Joystick_LeerY();

   Joystick_Direccion Joystick_ProcesarDir(uint16_t valorEjeX, uint16_t valorEjeY);
   void Joystick_LeerDirs(uint16_t valorEjeX, uint16_t valorEjeY, Joystick_Direccion* dirs);
   
/*==================[end of file]============================================*/
#endif /* _JOYSTICK_H_ */