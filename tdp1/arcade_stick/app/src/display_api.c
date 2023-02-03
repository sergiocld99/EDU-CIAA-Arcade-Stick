#include "display_api.h"

// Índice de caracteres personalizados
typedef enum {
   UP_ARROW, DOWN_ARROW, LEFT_ARROW, RIGHT_ARROW
} Display_Arrows;

// Prototipos de funciones privadas
static void Display_AddCustomChars();


// ---------------------- Funciones públicas -------------------------- //

void Display_Init(){
   
   // Inicializar LCD de 16x1 (caracteres x lineas) con cada caracter de 5x8 pixeles
   lcdInit( 16, 2, 5, 8 );
   
   delay( LCD_STARTUP_WAIT_MS );   // No compatible con FreeRTOS

   // Apagar el cursor
   lcdCursorSet( LCD_CURSOR_OFF );

   // Agregar caracteres personalizados
   Display_AddCustomChars();
}

void Display_WriteMessage(char* msg){
    // limpiar pantalla y ubicar cursor al inicio
   lcdClearAndHome();

   // Escribir mensaje de manera bloqueante
   lcdSendString(msg);
}

void Display_WriteDirs(bool_t up, bool_t left, bool_t right, bool_t down){
   
   // Ubicar cursor en la segunda fila
   lcdGoToXY(2, 1);
   if (left) lcdData(LEFT_ARROW);
   else lcdSendString(" ");

   lcdGoToXY(5, 1);
   if (up) lcdData(UP_ARROW);
   else lcdSendString(" ");

   lcdGoToXY(8, 1);
   if (down) lcdData(DOWN_ARROW);
   else lcdSendString(" ");

   lcdGoToXY(11, 1);
   if (right) lcdData(RIGHT_ARROW);
   else lcdSendString(" ");
}

// --------------------- Funciones privadas ------------------------ //

static void Display_AddCustomChars(){
   // Creado mediante Custom Character Generator - https://omerk.github.io/lcdchargen/

   const char upArrow[8] = {
	   0b00000,
	   0b00100,
	   0b01110,
	   0b10101,
	   0b00100,
	   0b00100,
	   0b00100,
	   0b00000
   };

   const char downArrow[8] = {
	   0b00000,
	   0b00100,
	   0b00100,
	   0b00100,
	   0b10101,
	   0b01110,
	   0b00100,
	   0b00000
   };

   const char leftArrow[8] = {
	   0b00000,
	   0b00000,
	   0b00100,
	   0b01000,
	   0b11111,
	   0b01000,
	   0b00100,
	   0b00000
   };

   const char rightArrow[8] = {
	   0b00000,
	   0b00000,
	   0b00100,
	   0b00010,
	   0b11111,
	   0b00010,
	   0b00100,
	   0b00000
   };

   lcdCreateChar( UP_ARROW, upArrow );
   lcdCreateChar( DOWN_ARROW, downArrow );
   lcdCreateChar( LEFT_ARROW, leftArrow );
   lcdCreateChar( RIGHT_ARROW, rightArrow );
}