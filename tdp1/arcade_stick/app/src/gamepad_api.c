/* --------------------------------------------------------

   Esta es una biblioteca simplificada para
   el manejo del driver USB desde el programa principal

/ ------------------------------------------------------- */

// Includes
#include "gamepad_api.h"

// Variables compartidas
static volatile int8_t X_VALUE = 0;
static volatile int8_t Y_VALUE = 0;

// Variable auxiliar: bits de pulsadores a enviar
static uint8_t aux_bitsPulsadores = 0x00;

// Prototipos de funciones privadas
static int8_t convertRawToSigned(uint16_t);


void checkForPressedButtons(void* unused)
{
   // Leer pulsadores y marcar seleccionados
   bool_t pulsados[CANT_PULSADORES];
   Buttons_Read(pulsados);

   for (uint8_t i=0; i<CANT_PULSADORES; i++){
      if (pulsados[i]) USB_MarcarBoton(i);
   }

   // Actualizar pulsadores activos en PC
   USB_PresionarBotones();

   // Enviar posición de los ejes X e Y
   usbDeviceGamepadMove(X_VALUE, 0);
   usbDeviceGamepadMove(Y_VALUE, 1);
   
   // Enviar estado del Switch
   usbDeviceGamepadHat(Joystick_LeerSwitch());
}


// ---------------------- Implementación de funciones públicas -------------------- //

bool_t USB_Init(){
   // Configurar driver y establecer conexión con PC
   bool_t driverSuccess = usbDeviceConfig(USB_HID_GAMEPAD);

   if (driverSuccess){
      // Asignar función de actualización de pulsadores
      usbDeviceGamepadCheckCallbackSet(checkForPressedButtons);
      return true;
   } else {
      return false;
   }

}

bool_t USB_Update(){
   // Leer eje X: el 0 está a la izquierda
   uint16_t valorEjeX = Joystick_LeerX();
      
   // Leer eje Y: el 0 está hacia arriba
   uint16_t valorEjeY = Joystick_LeerY();

   // Reducir valores al rango del driver
   X_VALUE = convertRawToSigned(valorEjeX);
   Y_VALUE = convertRawToSigned(valorEjeY);
      
   // Actualizar reporte
   return usbDeviceGamepadTasks();
}


bool_t USB_Attempt(){
   // No se realiza lectura del joystick, es una prueba de envío
   return usbDeviceGamepadTasks();
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

// ----------------------- Implementación de funciones privadas -----------------

static int8_t convertRawToSigned(uint16_t raw){
   uint8_t reduced = (uint8_t) (raw / 4);
   return (int8_t) (reduced - 128);
}