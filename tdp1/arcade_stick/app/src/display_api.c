#include "display_api.h"


void Display_Init(){
   
   // Inicializar LCD de 16x1 (caracteres x lineas) con cada caracter de 5x8 pixeles
   lcdInit( 16, 2, 5, 8 );
   
   delay( LCD_STARTUP_WAIT_MS );   // No compatible con FreeRTOS
   
   lcdCursorSet( LCD_CURSOR_OFF ); // Apaga el cursor
}

void Display_Write(char* msg){
   lcdClearAndHome();                     // Borrar la pantalla
   lcdSendString(msg);
}