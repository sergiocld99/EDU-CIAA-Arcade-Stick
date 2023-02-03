/*============================================================================
 * Licencia:
 * Autor:      Calder�n Sergio Leandro
 * Fecha:      1 de noviembre de 2022
 *===========================================================================*/

#ifndef _DISPLAY_API_H_
   #define _DISPLAY_API_H_

   /*==================[inclusiones]============================================*/
   
  

   /*==================[macros]=================================================*/

   #include "sapi.h"        // <= Biblioteca sAPI


   /*==================[tipos de datos declarados por el usuario]===============*/

   


   /*==================[declaraciones de datos externos]========================*/


   /*==================[declaraciones de funciones p�blicas]====================*/
   
   void Display_Init();

   void Display_WriteMessage(char* msg);

   void Display_WriteDirs(bool_t up, bool_t left, bool_t right, bool_t down);


/*==================[end of file]============================================*/

#endif