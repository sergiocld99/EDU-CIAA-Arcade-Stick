/*============================================================================
 * Licencia:
 * Autor:      Calderón Sergio Leandro
 * Fecha:      1 de noviembre de 2022
 *===========================================================================*/

#ifndef _JOYSTICK_H_
   #define _JOYSTICK_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi.h"
   #include "mapeoGpio.h"        // VRx, VRy, SW

   #include <stdlib.h>

   /*==================[macros]=================================================*/

   #define NEUTRO_MIN 400
   #define NEUTRO_MAX 624


   /*==================[tipos de datos declarados por el usuario]===============*/

   typedef enum {
      X_AXIS, Y_AXIS
   } Joystick_Axis;

   typedef enum {
      UP, LEFT, RIGHT, DOWN, NONE
   } Joystick_Direccion;


   /*==================[declaraciones de datos externos]========================*/

   /*==================[declaraciones de funciones públicas]====================*/
   
   // Inicialización de pines
   void Joystick_Init();

   // Lectura bloqueante de ejes y pulsador
   void Joystick_Read();

   // Obtención de estado del pulsador SW
   uint8_t Joystick_IsSwitchPressed();

   // Obtención de valores de ejes (posterior al Read)
   uint8_t Joystick_GetUnsignedAxisValue(Joystick_Axis axis);
   int8_t Joystick_GetSignedAxisValue(Joystick_Axis axis);

   // Cálculo de direcciones actuales (una para cada eje)
   void Joystick_GetDirections(Joystick_Direccion* dirs);
   


/*==================[end of file]============================================*/

#endif