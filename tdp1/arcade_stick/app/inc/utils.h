/*============================================================================
 * Licencia:
 * Autor: Calderón Sergio
 * Fecha: 24 de octubre de 2022
 *===========================================================================*/

#ifndef _UTILS_H_
   #define _UTILS_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi_datatypes.h"
   

   /*==================[macros]=================================================*/
   
   
   /*==================[tipos de datos declarados por el usuario]===============*/
   

   /*==================[declaraciones de datos externos]========================*/


   /*==================[declaraciones de funciones públicas]====================*/
   
   char* itoa(int value, char* result, int base);
   void encenderPares();
   void encenderImpares();
   void apagarPares();
   void apagarImpares();
   void apagarTodos();
   
#endif


