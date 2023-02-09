#ifndef _DISPLAY_API_H_
   #define _DISPLAY_API_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi.h"

   /*==================[declaraciones de funciones públicas]====================*/
   
   // Configura los parámetros del LCD y crea los caracteres de flechas
   void Display_Init();

   // Escribe el mensaje pasado por parámetro de forma bloqueante
   void Display_WriteMessage(char* msg);

   // Escribe las direcciones que se encuentren activas según parámetros
   void Display_WriteDirs(bool_t up, bool_t left, bool_t right, bool_t down);


/*==================[end of file]============================================*/

#endif