#include "buttons.h"

// Variables privadas
static uint8_t connectedPins[] = {PIN_S1, PIN_S2, PIN_S3, PIN_S4, PIN_S5, PIN_S6};
static bool_t lastValues[] = {false, false, false, false, false, false};
static bool_t confirmedValues[] = {false, false, false, false, false, false};

// Prototipos de funciones privadas
static void Buttons_Check(bool_t readValue, uint8_t position);

// ------------------------- Funciones públicas -----------------------------

void Buttons_Init()
{
    // Variables locales
    uint8_t i;

    // Establecer cada pin conectado a un botón como entrada
    for (i = 0; i < 6; i++)
    {
        gpioInit(connectedPins[i], GPIO_INPUT);
    }
}

void Buttons_Read(bool_t *values)
{
    // Variables locales
    bool_t readValue;
    uint8_t i;

    // Para cada pulsador del gamepad
    for (i = 0; i < 6; i++)
    {
        // Leer estado actual
        readValue = !gpioRead(connectedPins[i]);

        // Realizar chequeo anti-rebote
        Buttons_Check(readValue, i);

        values[i] = confirmedValues[i];
    }

}

// ------------------------- Funciones privadas -------------------------------

// Control anti-rebote: se requiere leer varias veces el mismo valor para confirmarlo
static void Buttons_Check(bool_t readValue, uint8_t position)
{

    // Si el nuevo valor leído es distinto al confirmado
    if (readValue != confirmedValues[position])
    {
        // Si el nuevo valor leído es igual al último leído
        if (readValue == lastValues[position])
        {
            // Confirmar valor
            confirmedValues[position] = readValue;         
        } else {
            // Sino, actualizar ultimo valor leido pero no confirmar
            lastValues[position] = readValue;
        }
    }
}