#ifndef _GAMEPAD_API_H_
   #define _GAMEPAD_API_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi.h"
   #include "usbd_gamepad.h"

   #include "joystick.h"      // lectura de ejes X,Y
   #include "buttons.h"       // Lectura de pulsadores 
   #include "mapeoGpio.h"
   
   
   /*==================[declaraciones de funciones públicas]====================*/
   
   // Configura el driver del gamepad para su utilización
   bool_t USB_Init();

   // Realiza una lectura de los controles y los envía a la PC
   bool_t USB_Update();

   // Realiza un envío de datos a la PC, devolviendo true si resultó exitoso
   bool_t USB_Attempt();

   /*==================[end of file]============================================*/
   
#endif