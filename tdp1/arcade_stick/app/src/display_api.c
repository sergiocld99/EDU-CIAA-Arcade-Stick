#include "display_api.h"


void Display_Init(){
   
   // Inicializar LCD de 16x1 (caracteres x lineas) con cada caracter de 5x8 pixeles
   lcdInit( 16, 1, 5, 8 );
   
   delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)
   
   lcdCursorSet( LCD_CURSOR_OFF ); // Apaga el cursor
   lcdClear();                     // Borrar la pantalla
   
}