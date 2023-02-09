#ifndef _MEF_H_
    #define _MEF_H_

    /*==================[inclusiones]============================================*/

    #include "components.h"
    #include "gamepad_api.h"

    /*============= [ declaración de funciones públicas ] ====================== */

    // Establece el estado inicial de la máquina de estados
    void MEF_Start();

    // Ejecuta el estado actual y establece el próximo
    void MEF_Update();

    /* ========================================================================= */

#endif 