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
   #include "joystick.h"
   #include "led.h"
   #include "display_api.h"
   // #include "display_16x1.h"
   
   // Utilidades
   #include "utils.h"
   #include <stdlib.h>
   #include <string.h>
   #include <stdio.h>
   
   // API simplificada para comunicación USB
   #include "gamepad_api.h"
   
   // Mapeo de los pines a utilizar para cada funcionalidad
   // Si está definida la macro "Depuracion" se usan leds y pulsadores ya incorporados
   #include "mapeoGpio.h"
   
   // Planificacion de tareas
   #include "FreeRTOS.h"
   #include "FreeRTOSConfig.h"
   #include "task.h"
   

   /*==================[macros]============================================*/
   
   // #define TICKRATE_HZ (1000)


#endif