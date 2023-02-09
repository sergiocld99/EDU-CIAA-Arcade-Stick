#ifndef _BUTTONS_H_
   #define _BUTTONS_H_

   /*==================[inclusiones]============================================*/
   
   #include "mapeoGpio.h"
   #include "sapi.h"

   /*==================[declaraciones de funciones públicas]====================*/
   
   // Establece los pines conectados a los pulsadores como entradas
   void Buttons_Init();

   // Realiza el barrido sobre los pulsadores considerando el efecto rebote
   // Devuelve por referencia los valores confirmados de cada botón (presionado = true)
   void Buttons_Read(bool_t* values);

/*==================[end of file]============================================*/

#endif