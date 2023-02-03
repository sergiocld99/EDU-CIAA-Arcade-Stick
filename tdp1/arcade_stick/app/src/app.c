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

// Prototipos de funciones privadas
bool_t tareaControles();
void mostrarErrorConexion();

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

void initComponents(){
   // Inicializar EDU-CIAA
   boardConfig();

   // Inicializar LED RGB
   LED_Init();

   // Inicializar joystick (ADC)
   Joystick_Init();

   // Inicializar pulsadores
   Buttons_Init();

   // Inicializar display
   delay(900);
   Display_Init();
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   /* ------------- INICIALIZACIONES ------------- */
   initComponents();
   MEF_Init();
   
   // Estado Conectando...
   LED_EncenderAzul();
   Display_Write("Conectando...");
   
   // Configuracion e Inicializacion de HID Gamepad
   bool_t driverSuccess = usbDeviceConfig(USB_HID_GAMEPAD);
   usbDeviceGamepadCheckCallbackSet(checkForPressedButtons);
   
   // DELAY NO ES COMPATIBLE CON FREERTOS
   delay(500);
   
   if (driverSuccess) {
      // Finalizo la inicializacion: Estado OK
      LED_EncenderVerde();
      Display_Write("Listo para jugar");
      gpioWrite(LEDG, ON);
   } else {
      mostrarErrorConexion();
   }
   

   // ---------- REPETIR POR SIEMPRE --------------------------

   bool_t success;

   while (1){
      success = tareaControles();
      
      if (success) delay(20);
      else {
         mostrarErrorConexion();
         while(!success);
      }
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}



// --------------- TAREAS A EJECUTAR ---------------------

bool_t tareaControles(){
   
   // Leer eje X: el 0 est� izquierda
   // EL EJE X DE NUESTRA PLACA EST� CONECTADO AL CANAL 2
   uint16_t valorEjeX = adcRead( CH2 );
      
   // Leer eje Y: el 0 est� arriba
   // EL EJE Y DE NUESTRA PLACA EST� CONECTADO AL CANAL 1
   uint16_t valorEjeY = adcRead( CH1 );
      
   // reducir entre 0 y 255
   uint8_t x_aux = (uint8_t) (valorEjeX / 4);
   uint8_t y_aux = (uint8_t) (valorEjeY / 4);
      
   // almacenar globalmente
   X_VALUE = (int8_t) (x_aux - 128);
   Y_VALUE = (int8_t) (y_aux - 128);
      
   // actualizar reporte
   return usbDeviceGamepadTasks();
}

void mostrarErrorConexion(){
   LED_EncenderRojo();
   Display_Write("USB incorrecto");
   
   gpioWrite(LEDG, OFF);
   gpioWrite(LEDR, ON);
}
