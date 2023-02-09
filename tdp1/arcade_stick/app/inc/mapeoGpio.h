// En este header se indica cual es el pin de EDU CIAA utilizado para 
// cada periférico del Arcade Stick

#ifndef _MAPEOGPIO_H_
   #define _MAPEOGPIO_H_

   /*==================[inclusiones]============================================*/
   
   // Cabecera donde se encuentran definidos los pines de la EDU-CIAA
   #include "sapi_peripheral_map.h"

   /*==================[macros]=================================================*/

   // #define DEPURACION

   // ---------------------------- joystick -------------------------

   #define PIN_VRX   CH2
   #define PIN_VRY   CH1
   #define PIN_SW    T_COL1

   // ---------------------------- pulsadores -----------------------

   #ifdef DEPURACION
      #define PIN_S1    TEC1
      #define PIN_S2    TEC2
      #define PIN_S3    TEC3
      #define PIN_S4    TEC4
   #else
      #define PIN_S1    GPIO3    
      #define PIN_S2    GPIO7   
      #define PIN_S3    GPIO6    
      #define PIN_S4    GPIO1  
   #endif
   
   #define PIN_S5    GPIO5   
   #define PIN_S6    GPIO8   

   // ---------------------------- display --------------------------

   #define PIN_LCD_E    LCDEN
   #define PIN_LCD_RS   LCDRS
   #define PIN_LCD_D4   LCD1    
   #define PIN_LCD_D5   LCD2   
   #define PIN_LCD_D6   LCD3     
   #define PIN_LCD_D7   LCD4    

   // ---------------------------- leds -------------------------------

   #ifdef DEPURACION
      #define PIN_LED_R    LEDR
      #define PIN_LED_G    LEDG
      #define PIN_LED_B    LEDB
   #else
      #define PIN_LED_R    T_FIL2  
      #define PIN_LED_G    T_COL0 
      #define PIN_LED_B    T_FIL3
   #endif


/*==================[end of file]============================================*/

#endif
