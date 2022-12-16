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
   // Testeado: OK
   if (!gpioRead(PIN_S1)) USB_MarcarBoton(0);
   if (!gpioRead(PIN_S2)) USB_MarcarBoton(1);
   if (!gpioRead(PIN_S3)) USB_MarcarBoton(2);
   if (!gpioRead(PIN_S4)) USB_MarcarBoton(3);   
   if (!gpioRead(PIN_S5)) USB_MarcarBoton(4);
   if (!gpioRead(PIN_S6)) USB_MarcarBoton(5);
   
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
   Display_Init();      // ESTO CAUSA UN BLOQUEO
   
   // Estado Conectando...
   LED_EncenderAzul();
   Display_Write("Conectando...");
   
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
   
   // NOTA: NO USAR DELAY() PORQUE ROMPE LA EJECUCIÓN
   // DELAY NO ES COMPATIBLE CON FREERTOS
   
   // Finalizo la inicializacion: Estado OK
   LED_EncenderVerde();
   Display_Write("Listo para jugar");
   
   gpioWrite(LEDG, ON);
   gpioWrite(T_COL0, ON);
   gpioWrite(T_FIL2, ON);
   gpioWrite(T_FIL3, ON);
   gpioWrite(T_FIL0, ON);
   
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
      
      // Leer eje X: el 0 está izquierda
      // EL EJE X DE NUESTRA PLACA ESTÁ CONECTADO AL CANAL 2
      uint16_t valorEjeX = adcRead( CH2 );
      
      // Leer eje Y: el 0 está arriba
      // EL EJE Y DE NUESTRA PLACA ESTÁ CONECTADO AL CANAL 1
      uint16_t valorEjeY = adcRead( CH1 );
      
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
