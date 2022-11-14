/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inclusiones

#include "app.h"         // <= Su propia cabecera

static volatile uint32_t tick_ct = 0;
static volatile uint8_t FLAG_UP = 0;
static volatile uint8_t FLAG_DOWN = 0;
static volatile uint8_t FLAG_LEFT = 0;
static volatile uint8_t FLAG_RIGHT = 0;
static volatile int8_t X_VALUE = 0;
static volatile int8_t Y_VALUE = 0;

void delayBloqueante(uint32_t ms){
   uint32_t end = tick_ct + ms;
   while (tick_ct < end) tick_ct++;
}

/* ESTO FUNCIONÓ EL 7/11 (PRESIONA 5 PRIMEROS BOTONES)
void checkForGamepadStatus(void* unused){
   usbDeviceGamepadPress(31);
}
*/

void checkForPressedButtons(void* unused)
{
   if (!gpioRead(PIN_SW)) USB_MarcarBoton(6);
   if (!gpioRead(PIN_S1)) USB_MarcarBoton(0);
   if (!gpioRead(PIN_S2)) USB_MarcarBoton(1);
   if (!gpioRead(PIN_S3)) USB_MarcarBoton(2);
   if (!gpioRead(PIN_S4)) USB_MarcarBoton(3);   
   
   USB_PresionarBotones();
   usbDeviceGamepadMove(X_VALUE, 0);
   usbDeviceGamepadMove(Y_VALUE, 1);
   usbDeviceGamepadHat(!gpioRead(PIN_SW));
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   SystemCoreClockUpdate();
   Board_Init();
   SysTick_Config(SystemCoreClock / TICKRATE_HZ);
   
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();
   
   // Inicializar componentes
   LED_Init();
   
   // Estado Conectando...
   LED_EncenderAzul();
   
   // Configuración/Inicialización de HID Gamepad
   usbDeviceConfig(USB_HID_GAMEPAD);
   usbDeviceGamepadCheckCallbackSet(checkForPressedButtons);
   
   // Habilitar ADC
   adcConfig( ADC_ENABLE ); /* ADC */
   
   // Habilitar UART (DEBUG)
   // Inicializar UART_USB a 115200 baudios
   uartConfig( UART_USB, 115200 );
   
   // Establecer T_COL1 como entrada digital
   gpioInit( T_COL1, GPIO_INPUT );
   
   // Finalizo la inicializacion: Estado OK
   LED_EncenderVerde();

   // ---------- REPETIR POR SIEMPRE --------------------------
   while (1) {
      
      // Leer entrada CH3 (eje X: el 0 está izquierda)
      uint16_t valorEjeX = adcRead( CH3 );
      
      // Leer entrada CH2 (eje Y: el 0 está arriba)
      uint16_t valorEjeY = adcRead( CH2 );
      
      Joystick_Direccion dirs[2];
      
      Joystick_LeerDirs(valorEjeX, valorEjeY, dirs);
      apagarTodos();
      
      FLAG_UP = 0;
      FLAG_DOWN = 0;
      FLAG_LEFT = 0;
      FLAG_RIGHT = 0;
      
      switch(dirs[0]){
         case NONE:
            break;
         case LEFT:
            Board_LED_Set(3, true);
            FLAG_LEFT = 1;
            break;
         case RIGHT:
            Board_LED_Set(4, true);
            FLAG_RIGHT = 0;
            break;
         default:
            break;
      }
      
      switch(dirs[1]){
         case NONE:
            break;
         case UP:
            Board_LED_Set(1, true);
            FLAG_UP = 1;
            break;
         case DOWN:
            Board_LED_Set(2, true);
            FLAG_DOWN = 1;
            break;
         default:
            break;
      }
      
      
      // achicar entre 0 y 255
      uint8_t x_aux = (uint8_t) (valorEjeX / 4);
      uint8_t y_aux = (uint8_t) (valorEjeY / 4);
      
      X_VALUE = (int8_t) (x_aux - 128);
      Y_VALUE = (int8_t) (y_aux - 128);
      
      usbDeviceGamepadTasks();
      sleepUntilNextInterrupt();
      
      // Board_LED_Toggle(5);
      delay(20);
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
