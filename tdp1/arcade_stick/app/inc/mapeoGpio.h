/*============================================================================
 * Licencia:
 * Autor:      Calderón Sergio Leandro
 * Fecha:      1 de noviembre de 2022
 *===========================================================================*/

// En este header se indica cual es
// el pin de EDU CIAA utilizado para 
// cada periférico del Arcade Stick

#ifndef _MAPEOGPIO_H_
   #define _MAPEOGPIO_H_

   /*==================[inclusiones]============================================*/
   
   // Cabecera donde se encuentran definidos los pines de la EDU-CIAA
   #include "sapi_peripheral_map.h"

   /*==================[macros]=================================================*/

   #define DEPURACION

   // ---------------------------- joystick -------------------------

   #define PIN_VRX     CH3
   #define PIN_VRY     CH2
   #define PIN_SW      T_COL1

   // ---------------------------- pulsadores -----------------------





   // ---------------------------- display --------------------------




   // ---------------------------- leds -------------------------------


/*==================[end of file]============================================*/

#endif
