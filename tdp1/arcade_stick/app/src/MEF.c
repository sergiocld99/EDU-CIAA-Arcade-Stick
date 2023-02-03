#include "MEF.h"

// Declaración de estados
typedef enum {
    CONNECTING, FAIL, CHECKING, READY
} MEF_Status;

// Variables privadas
static MEF_Status status;

// ------------------------- Prototipos de funciones privadas ------------------ //

// Funciones propias de cada estado
static void MEF_Connecting();
static void MEF_Fail();
static void MEF_Checking();
static void MEF_Ready();

// Punteros a funciones de estado
static void (*MEF_Functions[])(void) = {
    MEF_Connecting, MEF_Fail, MEF_Checking, MEF_Ready
};

// ------------------------- Implementación de funciones públicas ---------------- //

void MEF_Start(){
    // Establecer estado inicial
    status = CONNECTING;
}

void MEF_Update(){
    // Invocar función correspondiente al estado actual
    (*MEF_Functions[status])();
}

// --------------------- Implementación de funciones de estado ------------------- //

static void MEF_Connecting(){

    // Encender LED azul
    LED_EncenderAzul();

    // Mostrar mensaje "Conectando..." en el display
    Display_WriteMessage("Conectando...");

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
        Display_WriteMessage("USB incorrecto");

        // Marcar como impreso para evitar reescribir en display
        printed = true;
    }
    
}

static void MEF_Checking(){
    static uint16_t attempts = 0;
    
    // Alternar led azul cada 25 x 20 ms = 500 ms
    LED_Alternar(25);

    // Realizar intento de envío de datos
    bool_t success = USB_Attempt();
    
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
        Display_WriteMessage("Listo para jugar");

        // Marcar como impreso para evitar reescribir en display
        printed = true;
    }

    // Realizar lectura de controles y enviarlo a PC
    bool_t success = USB_Update();

    // Pasar a estado FAIL si el envío no fue exitoso
    if (!success) status = FAIL;
    else {
        bool_t up, left, right, down;

        Joystick_GetDirs(&up, &left, &right, &down);
        Display_WriteDirs(up, left, right, down);
    }
}