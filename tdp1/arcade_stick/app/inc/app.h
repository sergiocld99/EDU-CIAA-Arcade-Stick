/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _APP_H_
   #define _APP_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi.h"        // <= Biblioteca sAPI
   
   // Perifericos
   #include "led.h"
   #include "joystick.h"
   #include "buttons.h"
   #include "display_api.h"
   // #include "display_16x1.h"

   // Máquina de estados
   #include "MEF.h"
   
   // Utilidades
   #include "utils.h"
   #include <stdlib.h>
   #include <string.h>
   #include <stdio.h>
   
   // API simplificada para comunicaci�n USB
   #include "gamepad_api.h"
   
   // Mapeo de los pines a utilizar para cada funcionalidad
   // Si est� definida la macro "Depuracion" se usan leds y pulsadores ya incorporados
   #include "mapeoGpio.h"
   

   /*==================[macros]============================================*/
   
   // #define TICKRATE_HZ (1000)


#endif