/* --------------------------------------------------------

   Esta es una biblioteca simplificada para
   el manejo del driver USB desde el programa principal

/ ------------------------------------------------------- */

// Includes
#include "sapi_datatypes.h"
#include "usbd_gamepad.h"

// Variable auxiliar: bits de pulsadores a enviar
static uint8_t aux_bitsPulsadores = 0x00;
static uint16_t ant_valorEjeX = 512;
static uint16_t ant_valorEjeY = 512;

int8_t USB_ValorX(uint16_t valor){
   int8_t diff = (int8_t) (valor - ant_valorEjeX);
   ant_valorEjeX = valor;
   
   return diff;
}

uint8_t USB_MarcarBoton(uint8_t numero){
   if (numero >= CANT_PULSADORES) return 0;
   
   // Los bits correspondientes a cada pulsador están
   // ordenados del menos al más significativo.
   
   // Ejemplo: 31 representa a los primeros 5 pulsadores activos
   
   aux_bitsPulsadores |= (1 << numero);
   return 1;
}

void USB_PresionarBotones(){
   // Escribir el byte del reporte correspondiente a los pulsadores
   usbDeviceGamepadPress(aux_bitsPulsadores);
   
   // Una vez enviado, se reinicia para la próxima iteración
   aux_bitsPulsadores = 0x00;
}