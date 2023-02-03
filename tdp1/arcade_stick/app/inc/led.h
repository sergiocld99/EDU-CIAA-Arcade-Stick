/*============================================================================
 * Licencia:
 * Autor:      Calder�n Sergio Leandro
 * Fecha:      1 de noviembre de 2022
 *===========================================================================*/

#ifndef _LED_H_
   #define _LED_H_

   /*==================[inclusiones]============================================*/
   
   #include "mapeoGpio.h"        // pines indicados para cada led
   #include "sapi.h"             // para gpioInit() y gpioWrite()


   /*==================[declaraciones de funciones p�blicas]====================*/
   
   // Configura los pines utilizados como salida
   void LED_Init();
   
   void LED_Alternar(uint8_t periodo);

   void LED_ApagarTodos();
   void LED_EncenderRojo();
   void LED_EncenderVerde();
   void LED_EncenderAzul();


/*==================[end of file]============================================*/

#endif