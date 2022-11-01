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

   #define PIN_VRX   CH3
   #define PIN_VRY   CH2
   #define PIN_SW    T_COL1

   // ---------------------------- pulsadores -----------------------

   #define PIN_S1    GPIO1
   #define PIN_S2    GPIO3
   #define PIN_S3    GPIO5
   #define PIN_S4    GPIO7
   #define PIN_S5    GPIO8
   #define PIN_S6    GPIO6

   // ---------------------------- display --------------------------

   #define PIN_LCD_E    LCDEN
   #define PIN_LCD_RS   LCDRS
   #define PIN_LCD_D4   LCD1
   #define PIN_LCD_D5   LCD2
   #define PIN_LCD_D6   LCD3
   #define PIN_LCD_D7   LCD4

   // ---------------------------- leds -------------------------------

   #define PIN_LED_R    GPIO0
   #define PIN_LED_G    GPIO2
   #define PIN_LED_B    GPIO4


/*==================[end of file]============================================*/

#endif
