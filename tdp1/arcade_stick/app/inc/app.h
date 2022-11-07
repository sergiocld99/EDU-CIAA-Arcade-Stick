/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _APP_H_
   #define _APP_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi.h"        // <= Biblioteca sAPI
   #include <stdlib.h>
   #include <string.h>
   #include <stdio.h>
   
   #include "joystick.h"
   #include "utils.h"
   
   // API simplificada para comunicación USB
   #include "gamepad_api.h"
   
   // Mapeo de los pines a utilizar para cada funcionalidad
   // Si está definida la macro "Depuracion" se usan leds y pulsadores ya incorporados
   #include "mapeoGpio.h"
   

   /*==================[macros]============================================*/
   
   #define TICKRATE_HZ (1000)


#endif