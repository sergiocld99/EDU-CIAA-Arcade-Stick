/*============================================================================
 * Licencia:
 * Autor:      Calder�n Sergio Leandro
 * Fecha:      1 de noviembre de 2022
 *===========================================================================*/

// En este header se indica cual es
// el pin de EDU CIAA utilizado para 
// cada perif�rico del Arcade Stick

#ifndef _MAPEOGPIO_H_
   #define _MAPEOGPIO_H_

   /*==================[inclusiones]============================================*/
   
   // Cabecera donde se encuentran definidos los pines de la EDU-CIAA
   #include "sapi_peripheral_map.h"

   /*==================[macros]=================================================*/

   // #define DEPURACION

   // ---------------------------- joystick -------------------------

   #define PIN_VRX   CH3
   #define PIN_VRY   CH2
   #define PIN_SW    T_COL1

   // ---------------------------- pulsadores -----------------------

   #ifdef DEPURACION
      #define PIN_S1    TEC1
      #define PIN_S2    TEC2
      #define PIN_S3    TEC3
      #define PIN_S4    TEC4
   #else
      #define PIN_S1    GPIO3    // ex GPIO1
      #define PIN_S2    GPIO7    // ex GPIO3
      #define PIN_S3    GPIO6    // ex GPIO5
      #define PIN_S4    GPIO1    // ex GPIO7
   #endif
   
   #define PIN_S5    GPIO5    // ex GPIO8
   #define PIN_S6    GPIO8    // ex GPIO6

   // ---------------------------- display --------------------------

   #define PIN_LCD_E    LCDEN
   #define PIN_LCD_RS   LCDRS
   #define PIN_LCD_D4   LCD1     // ex LCD1
   #define PIN_LCD_D5   LCD2     // ex LCD2
   #define PIN_LCD_D6   LCD3     // ex LCD3
   #define PIN_LCD_D7   LCD4     // ex LCD4

   // ---------------------------- leds -------------------------------

   #ifdef DEPURACION
      #define PIN_LED_R    LEDR
      #define PIN_LED_G    LEDG
      #define PIN_LED_B    LEDB
   #else
      // Verificado
      #define PIN_LED_R    T_FIL2      // ex GPIO0
      #define PIN_LED_G    T_COL0      // ex GPIO2
      #define PIN_LED_B    T_FIL3      // ex GPIO4
   #endif


/*==================[end of file]============================================*/

#endif
