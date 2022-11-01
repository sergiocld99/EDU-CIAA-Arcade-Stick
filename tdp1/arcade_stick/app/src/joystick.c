#include "joystick.h"

// Variables privadas
static uint16_t AXIS_X_RAW_VALUE = 512;
static uint16_t AXIS_Y_RAW_VALUE = 512;
static uint8_t SWITCH_PRESSED = 0;

// Prototipos de funciones privadas
static uint8_t convert16to8(uint16_t ogValue);
static int8_t convertRawToSigned(uint16_t ogValue);


void Joystick_Init(){
   // Los pines VRX y VRY ya están definidos como entradas analógicas (por Board Init)
   // Establecemos a SW como entrada digital
   gpioInit(PIN_SW, GPIO_INPUT);

   // Habilitar ADC
   adcConfig(ADC_ENABLE);
}

void Joystick_Read(){
   // Como se dispone de un único conversor ADC, primero se lee X y luego Y
   AXIS_X_RAW_VALUE = adcRead(PIN_VRX);
   AXIS_Y_RAW_VALUE = adcRead(PIN_VRY);

   // También se lee el estado del pulsador SW
   SWITCH_PRESSED = !gpioRead(PIN_SW);
}

uint8_t Joystick_IsSwitchPressed(){
   return SWITCH_PRESSED;
}

uint8_t Joystick_GetUnsignedAxisValue(Joystick_Axis axis){
   switch(axis){
      case X_AXIS:
         return convert16to8(AXIS_X_RAW_VALUE);
      case Y_AXIS:
         return convert16to8(AXIS_Y_RAW_VALUE);
      default:
         return 0;
   }
}

int8_t Joystick_GetSignedAxisValue(Joystick_Axis axis){
   switch(axis){
      case X_AXIS:
         return convertRawToSigned(AXIS_X_RAW_VALUE);
      case Y_AXIS:
         return convertRawToSigned(AXIS_Y_RAW_VALUE);
      default:
         return 0;
   }
}

void Joystick_GetDirections(Joystick_Direccion* dirs){
   if (AXIS_X_RAW_VALUE > NEUTRO_MIN && AXIS_X_RAW_VALUE < NEUTRO_MAX) dirs[0] = NONE;
   else if (AXIS_X_RAW_VALUE <= NEUTRO_MIN) dirs[0] = LEFT;
   else dirs[0] = RIGHT;
      
   if (AXIS_Y_RAW_VALUE > NEUTRO_MIN && AXIS_Y_RAW_VALUE < NEUTRO_MAX) dirs[1] = NONE;
   else if (AXIS_Y_RAW_VALUE <= NEUTRO_MIN) dirs[1] = UP;
   else dirs[1] = DOWN;
}


// ----------------------- Funciones privadas ------------------------

// Función para convertir un valor entre 0 y 1023 a su equivalente entre 0 y 255
static uint8_t convert16to8(uint16_t ogValue){
   return (uint8_t) (ogValue / 4);
}

static int8_t convertRawToSigned(uint16_t ogValue){
   uint8_t unsignedValue = convert16to8(ogValue);
   return (int8_t) (unsignedValue - 128);
}
