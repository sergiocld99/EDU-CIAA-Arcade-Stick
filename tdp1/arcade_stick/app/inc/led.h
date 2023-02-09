#ifndef _LED_H_
   #define _LED_H_

   /*==================[inclusiones]============================================*/
   
   #include "mapeoGpio.h"        // pines indicados para cada led
   #include "sapi.h"             // para gpioInit() y gpioWrite()

   /*==================[macros]============================================*/

   // #define ANODO_COMUN
   #define CATODO_COMUN

   #ifdef ANODO_COMUN
      // El terminal común es VCC
      #define ENCENDIDO OFF
      #define APAGADO ON
   #else
      // El terminal común es GND
      #define ENCENDIDO ON
      #define APAGADO OFF
   #endif

   /*==================[declaraciones de funciones públicas]====================*/
   
   // Configura los pines utilizados como salida
   void LED_Init();

   // Apaga los 3 diodos del LED
   void LED_ApagarTodos();

   // Funciones para encender un color del LED
   void LED_EncenderRojo();
   void LED_EncenderVerde();
   void LED_EncenderAzul();


   // Apaga o enciende el último LED modificado
   void LED_Alternar(uint8_t periodo);

/*==================[end of file]============================================*/

#endif