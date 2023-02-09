/*============================================================================
 * Autor:         Blanco Valentín, Bonifacio Lucas y Calderón Sergio
 * Fecha:         6 de febrero de 2023
 *===========================================================================*/

// Cabecera del archivo
#include "app.h"

// Prototipos de funciones privadas
static void initComponents();


// ------------------------- Implementación de funciones públicas --------------- //

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   /* ------------- INICIALIZACIONES ------------- */
   
   // Inicializar periféricos
   initComponents();

   // Iniciar máquina de estados (Conectando...)
   MEF_Start();

   // ---------- REPETIR POR SIEMPRE --------------------------

   while (1){
      // Actualizar estado con frecuencia 50 Hz
      MEF_Update();
      delay(20);
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

// -------------------------------- Funciones privadas ------------------------

static void initComponents(){
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
