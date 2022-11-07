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
   if (!gpioRead(TEC1)) USB_MarcarBoton(1);
   if (!gpioRead(TEC2)) USB_MarcarBoton(2);
   if (!gpioRead(TEC3)) USB_MarcarBoton(3);
   if (!gpioRead(TEC4)) USB_MarcarBoton(4);   
   
   USB_PresionarBotones();
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

   // ---------- REPETIR POR SIEMPRE --------------------------
   while (1) {
      
      // Leer entrada CH3 (eje X: el 0 está izquierda)
      uint16_t valorEjeX = adcRead( CH3 );
      
      // Leer entrada CH2 (eje Y: el 0 está arriba)
      uint16_t valorEjeY = adcRead( CH2 );
      
      // MANDAR VALOR DE EJE X a TERMINAL
      /*
      char textoX[5], textoY[5];
      itoa(valorEjeX, textoX, 10);
      itoa(valorEjeY, textoY, 10);
      uartWriteString( UART_USB, textoX );
      uartWriteString( UART_USB, ", ");
      uartWriteString( UART_USB, textoY );
      uartWriteString( UART_USB, "\r\n");
      delay(1000);
      */
      
      Joystick_Direccion dirs[2];
      
      Joystick_LeerDirs(valorEjeX, valorEjeY, dirs);
      // apagarTodos();
      
      FLAG_UP = 0;
      FLAG_DOWN = 0;
      FLAG_LEFT = 0;
      FLAG_RIGHT = 0;
      
      switch(dirs[0]){
         case NONE:
            break;
         case LEFT:
            // Board_LED_Set(3, true);
            FLAG_LEFT = 1;
            break;
         case RIGHT:
            // Board_LED_Set(4, true);
            FLAG_RIGHT = 0;
            break;
         default:
            break;
      }
      
      switch(dirs[1]){
         case NONE:
            break;
         case UP:
            // Board_LED_Set(0, true);
            FLAG_UP = 1;
            break;
         case DOWN:
            // Board_LED_Set(1, true);
            FLAG_DOWN = 1;
            break;
         default:
            break;
      }
      
      // Lectura del botón SW
      /*
      if( !gpioRead( T_COL1 ) ){
         Board_LED_Set(5, true);
      } else Board_LED_Set(5, false);
      */
      
      usbDeviceGamepadPress(100);
      
      uint8_t sent = usbDeviceGamepadTasks();
      sleepUntilNextInterrupt();
      
      // Board_LED_Toggle(5);
      delay(200);
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
