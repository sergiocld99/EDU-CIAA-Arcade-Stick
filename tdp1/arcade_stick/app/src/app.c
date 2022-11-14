/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Cabecera del archivo
#include "app.h"

// Variables compartidas
static volatile int8_t X_VALUE = 0;
static volatile int8_t Y_VALUE = 0;

// Prototipos de tareas
void tareaControles(void*);

void checkForPressedButtons(void* unused)
{
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
   
   
   // ---------- PLANIFICACION DE TAREAS ----------------------

   // Crear tarea en freeRTOS
   xTaskCreate(
      tareaControles,               // Funcion de la tarea a ejecutar
      (const char *) "Controles",   // Nombre de la tarea como String amigable para el usuario
      configMINIMAL_STACK_SIZE*2,   // Cantidad de stack de la tarea
      0,                            // Parametros de tarea
      tskIDLE_PRIORITY+1,           // Prioridad de la tarea
      0                             // Puntero a la tarea creada en el sistema
   );
   
   // Iniciar scheduler
   vTaskStartScheduler();
   

   // ---------- REPETIR POR SIEMPRE --------------------------

   while (1);

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}



// --------------- TAREAS A EJECUTAR ---------------------

void tareaControles(void* params){
   
   // Tarea periodica cada 20 ms
   portTickType xPeriodicity =  20 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();
   
   // Repetir por siempre
   while(1){
      
      // Leer entrada CH3 (eje X: el 0 está izquierda)
      uint16_t valorEjeX = adcRead( CH3 );
      
      // Leer entrada CH2 (eje Y: el 0 está arriba)
      uint16_t valorEjeY = adcRead( CH2 );
      
      // reducir entre 0 y 255
      uint8_t x_aux = (uint8_t) (valorEjeX / 4);
      uint8_t y_aux = (uint8_t) (valorEjeY / 4);
      
      // almacenar globalmente
      X_VALUE = (int8_t) (x_aux - 128);
      Y_VALUE = (int8_t) (y_aux - 128);
      
      // actualizar reporte
      usbDeviceGamepadTasks();
      
      // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
      vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
   
}
