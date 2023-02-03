#include "MEF.h"

typedef enum {
    CONNECTING, FAIL, CHECKING, READY
} MEF_Status;

MEF_Status status;

// ------------------------- Prototipos de funciones privadas ------------------ //

// Funciones propias de cada estado
static void MEF_Connecting();
static void MEF_Fail();
static void MEF_Checking();
static void MEF_Ready();

// ------------------------- Implementación de funciones públicas ---------------- //

void MEF_Start(){
    status = CONNECTING;
}

void MEF_Update(){
    switch(status){
        case CONNECTING: 
            MEF_Connecting();
            break;
        case FAIL:
            MEF_Fail();
            break;
        case CHECKING:
            MEF_Checking();
            break;
        case READY:
            MEF_Ready();
            break;
        default:
            break;
    }
}

// ------------------------- Implementación de funciones privadas ------------------- //

static void MEF_Connecting(){

    // Encender LED azul
    LED_EncenderAzul();

    // Mostrar mensaje "Conectando..." en el display
    Display_Write("Conectando...");

    // Establecer conexión con PC
    bool_t success = USB_Init();

    // Si el dispositivo fue reconocido, pasar a fase de chequeo
    if (success) status = CHECKING;
    else status = FAIL;
}


static void MEF_Fail(){
    static bool_t printed = false;

    if (!printed){
        // Mantener encendido el LED rojo
        LED_EncenderRojo();

        // Mostrar mensaje "USB incorrecto" por display
        Display_Write("USB incorrecto");

        // Marcar como impreso para evitar reescribir en display
        printed = true;
    }
    
}

static void MEF_Checking(){
    static uint16_t attempts = 0;
    
    // Alternar led azul cada 15 x 20 ms = 300 ms
    LED_Alternar(15);

    // Realizar intento
    bool_t success = USB_Update();
    
    // Si fue exitoso, pasar a estado Ready
    // en caso contrario, luego de 500 intentos (10s), pasar a Fail
    if (success) status = READY;
    else if (++attempts == 500) status = FAIL;
}


static void MEF_Ready(){
    static bool_t printed = false;

    if (!printed){
        // Mantener encendido el LED verde
        LED_EncenderVerde();

        // Mostrar mensaje "Listo para jugar" por display
        Display_Write("Listo para jugar");

        // Marcar como impreso para evitar reescribir en display
        printed = true;
    }

    // Realizar lectura de controles y enviarlo a PC
    bool_t success = USB_Update();

    // Pasar a estado FAIL si el envío no fue exitoso
    if (!success) status = FAIL;
}