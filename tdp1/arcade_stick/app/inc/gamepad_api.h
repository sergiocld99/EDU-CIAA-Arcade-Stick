#ifndef _GAMEPAD_API_H_
   #define _GAMEPAD_API_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi.h"
   #include "usbd_gamepad.h"

   #include "joystick.h"      // lectura de ejes X,Y
   #include "mapeoGpio.h"
   
   /*==================[definici�n de tipos]============================================*/
   
   
   /*==================[declaraciones de funciones públicas]====================*/
   
   bool_t USB_Init();


   bool_t USB_Update();


   bool_t USB_Attempt();
   
   uint8_t USB_MarcarBoton(uint8_t numero);
   void USB_PresionarBotones();

   /*==================[end of file]============================================*/
   
#endif