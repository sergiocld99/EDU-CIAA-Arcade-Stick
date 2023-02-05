// Cabecera del archivo
#include "led.h"

// Variables privadas
static uint8_t ledEncendido = 0;
static bool_t apagado = true;

// Prototipos de funciones privadas
static void LED_Apagar(uint8_t);
static void LED_Encender(uint8_t);

// --------------------------- Funciones públicas -----------------------

void LED_Init(){
   gpioInit(PIN_LED_R, GPIO_OUTPUT);
   gpioInit(PIN_LED_G, GPIO_OUTPUT);
   gpioInit(PIN_LED_B, GPIO_OUTPUT);
}

void LED_Alternar(uint8_t periodo){
   static uint8_t count = 0;

   if (++count == periodo){
      if (ledEncendido > 0){
         if (apagado) LED_Encender(ledEncendido);
         else LED_Apagar(ledEncendido);
      }

      count = 0;
   }
}

void LED_ApagarTodos(){
   LED_Apagar(PIN_LED_R);
   LED_Apagar(PIN_LED_G);
   LED_Apagar(PIN_LED_B);
}

void LED_EncenderRojo(){
   LED_ApagarTodos();
   LED_Encender(PIN_LED_R);
}

void LED_EncenderVerde(){
   LED_ApagarTodos();
   LED_Encender(PIN_LED_G);
}

void LED_EncenderAzul(){
   LED_ApagarTodos();
   LED_Encender(PIN_LED_B);
}

// -------------------------- Funciones privadas -------------------------

static void LED_Apagar(uint8_t id){
   gpioWrite(id, APAGADO);
   apagado = true;
}

static void LED_Encender(uint8_t id){
   gpioWrite(id, ENCENDIDO);
   ledEncendido = id;
   apagado = false;
}